/*!
 * \file imageprocessor.cpp
 * \brief Implementation of the methods of the ImageProcessor declared in the imageprocessor.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.1
 */

#include "imageprocessor.hpp"

#include <QImage>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>

#if NON_FREE == 1
    # include <opencv2/nonfree/features2d.hpp>
#endif

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
ImageProcessor::ImageProcessor() {}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
ImageProcessor::~ImageProcessor() {}

/**************************************************************
 **************************************************************
 *
 * OpenCv Mat to Qimage.
 *
 **************************************************************/
QImage ImageProcessor::cvMatToImage(const cv::Mat& image)
{
    switch(image.type())
    {
        // 8-bits, 4 channels
        case CV_8UC4:
        {
            QImage im(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_ARGB32);
            return im;
        }

        // 8-bit, 3 channels
        case CV_8UC3:
        {
            QImage im(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_RGB888 );
            return im.rgbSwapped();
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
            static QVector<QRgb> sColorTable(256);

            if(sColorTable.isEmpty())
            {
                for (int i = 0; i < 256; ++i)
                {
                    sColorTable[i] = qRgb(i, i, i);
                }
            }

            QImage im(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_Indexed8);
            im.setColorTable(sColorTable);
            return im;
        }
    }

    return QImage();
}

/**************************************************************
 **************************************************************
 *
 * Qimage to OpenCV Mat.
 *
 **************************************************************/
cv::Mat ImageProcessor::imageToCvMat(const QImage& image)
{
    cv::Mat mata = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
    cv::Mat matb = cv::Mat(mata.rows, mata.cols, CV_8UC3);
    int from_to[] = {0, 0, 1, 1, 2, 2};

    cv::mixChannels(&mata, 1, &matb, 1, from_to, 3);
    return matb;
}

/**************************************************************
 **************************************************************
 *
 * Split.
 *
 **************************************************************/
void ImageProcessor::split(const cv::Mat& input, cv::Mat& outputLeft, cv::Mat& outputRight)
{
    cv::Mat tmp = input(cv::Rect(0, 0, input.cols / 2, input.rows));
    tmp.copyTo(outputLeft);

    tmp = input(cv::Rect(input.cols / 2, 0, input.cols / 2, input.rows));
    tmp.copyTo(outputRight);
}

/**************************************************************
 **************************************************************
 *
 * Blur.
 *
 **************************************************************/
void ImageProcessor::blur(cv::Mat& image, int kernel_size)
{
    cv::Mat dst = image.clone();
    cv::blur(image, dst, cv::Size(kernel_size, kernel_size));
    image = dst;
}

/**************************************************************
 **************************************************************
 *
 * Sobel.
 *
 **************************************************************/
void ImageProcessor::sobel(cv::Mat& image, int kernel_size, int scale)
{
  int dx = 1;   //derivate x
  int dy = 0;   //derivate y

  cv::Mat dst = image.clone();
  cv::Sobel(image, dst, image.depth(), dx, dy, kernel_size, scale);

  image = dst;
}

/**************************************************************
 **************************************************************
 *
 * Canny.
 *
 **************************************************************/
void ImageProcessor::canny(cv::Mat& image, int kernel_size, double threshold, int ratio)
{
  cv::Mat src = image.clone();
  cv::Mat gray, edge, dst;
  cv::cvtColor(src, gray, CV_BGR2GRAY);

  cv::Canny(gray, edge, threshold, threshold * ratio, kernel_size);
  edge.convertTo(dst, CV_8U);
  cv::cvtColor(dst, dst, CV_GRAY2BGR);

  image = dst;
}

/**************************************************************
 **************************************************************
 *
 * Disparity map.
 *
 **************************************************************/
cv::Mat ImageProcessor::disparityMap(cv::Mat& leftImage, cv::Mat& rightImage, StereoMode mode)
{
    cv::Mat disp16 = cv::Mat(leftImage.rows, leftImage.cols, CV_16S);
    cv::Mat disp8 = cv::Mat(leftImage.rows, leftImage.cols, CV_8UC1);
    cv::Mat lImg, dImg;

    cv::cvtColor(leftImage, lImg, CV_BGR2GRAY);
    cv::cvtColor(rightImage, dImg, CV_BGR2GRAY);
    lImg.convertTo(lImg, CV_8UC1);
    dImg.convertTo(dImg, CV_8UC1);

    int ratio = 7;
    int numDisp = ratio * 16;
    int SADWindowSize = 21;
    
    switch(mode)
    {
        case ImageProcessor::StereoMode::STEREO_MODE_BM:
        {
            cv::StereoBM sbm = cv::StereoBM(cv::StereoBM::BASIC_PRESET, numDisp, SADWindowSize);
            sbm(lImg, dImg, disp16);
            break;
        }

        case ImageProcessor::StereoMode::STEREO_MODE_SGBM:
        {
            int minDisp = 0;
            cv::StereoSGBM sgbm = cv::StereoSGBM(minDisp, numDisp, SADWindowSize);
            sgbm(lImg, dImg, disp16);
            break;
        }
    }
    
    double minVal; double maxVal;
    cv::minMaxLoc(disp16, &minVal, &maxVal);

    disp16.convertTo(disp16, CV_8UC1, 255/(maxVal - minVal));
    cv::cvtColor(disp16, disp16, CV_GRAY2BGR);
    cv::normalize(disp16, disp8, 0, 255, CV_MINMAX, CV_8U);
    
    return disp16;
}

#if NON_FREE == 1
    cv::Mat ImageTools::flann(cv::Mat& img_gauche, cv::Mat img_droite){

        int minHessian = 400;

        cv::SurfFeatureDetector detector (minHessian);
        std::vector<cv::KeyPoint> keypoints_1, keypoints_2;

        detector.detect( img_droite, keypoints_1 );
        detector.detect( img_gauche, keypoints_2 );

        cv::SurfDescriptorExtractor extractor;
        cv::Mat descriptors_1, descriptors_2;
        
        extractor.compute(img_droite, keypoints_1, descriptors_1);
        extractor.compute(img_gauche, keypoints_2, descriptors_2);
    
        cv::FlannBasedMatcher matcher;
        std::vector<cv::DMatch> matches;

        matcher.match(descriptors_1, descriptors_2, matches);
        
        double max_dist = 0; 
        double min_dist = 100;
        double dist;

        for (int i=0; i<descriptors_1.rows; i++){
            dist = matches[i].distance;
            if (dist < min_dist) min_dist = dist;
            if (dist > max_dist) max_dist = dist;
        }

        std::vector<cv::DMatch> good_matches;
        for (int i=0; i<descriptors_1.rows; i++){
            if (matches[i].distance <= cv::max(2*min_dist, 0.02))
                good_matches.push_back( matches[i]);
        }
        
        cv::Mat img;
        drawMatches( img_droite, keypoints_1, img_gauche, keypoints_2,
                good_matches, img, cv::Scalar::all(-1), cv::Scalar::all(-1),
                std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
        return img;
    }

#endif
