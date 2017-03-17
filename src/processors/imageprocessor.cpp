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

#include "processors/imageprocessor.hpp"

#include "parameters/disparitymapparameters.hpp"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include <QImage>

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
QImage ImageProcessor::cvMatToImage(const cv::Mat& image) const
{
    switch(image.type())
    {
        // 8-bits, 4 channels
        case CV_8UC4:
        {
            QImage im(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_ARGB32);
            return im.copy();
        }

        // 8-bit, 3 channels
        case CV_8UC3:
        {
            QImage im(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_RGB888);
            return im.rgbSwapped().copy();
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
            QImage im(image.data, image.cols, image.rows, static_cast<int>(image.step), QImage::Format_Indexed8);
            return im.copy();
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
cv::Mat ImageProcessor::imageToCvMat(const QImage& image) const
{
    cv::Mat matA = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
    cv::Mat matB = cv::Mat(matA.rows, matA.cols, CV_8UC3);
    int fromTo[] = {0, 0, 1, 1, 2, 2};

    cv::mixChannels(&matA, 1, &matB, 1, fromTo, 3);
    return matB;
}

/**************************************************************
 **************************************************************
 *
 * Split.
 *
 **************************************************************/
void ImageProcessor::split(const cv::Mat& input, cv::Mat& outputLeft, cv::Mat& outputRight) const
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
void ImageProcessor::blur(cv::Mat& image, int kernelWidth, int kernelHeight) const
{
    cv::blur(image, image, cv::Size(kernelWidth, kernelHeight));
}

/**************************************************************
 **************************************************************
 *
 * Sobel.
 *
 **************************************************************/
void ImageProcessor::sobel(cv::Mat& image, int destDepth, int derX, int derY, int kernelSize,  double scale, double delta) const
{
    cv::Mat dst = image.clone();

    try
    {
        cv::Sobel(image, dst, destDepth, derX, derY, kernelSize, scale, delta);
    }
    catch(const cv::Exception&)
    {
        throw;
    }


    image = dst;
}

/**************************************************************
 **************************************************************
 *
 * Canny.
 *
 **************************************************************/
void ImageProcessor::canny(cv::Mat& image, double histThrA, double histThrB, int aperture, bool gradientMagnitude) const
{
    cv::Mat src = image.clone();
    cv::Mat gray, edge, dst;
    cv::cvtColor(src, gray, CV_BGR2GRAY);
    cv::Canny(gray, edge, histThrA, histThrB, aperture, gradientMagnitude);
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
const cv::Mat& ImageProcessor::disparityMap(cv::Mat leftImage, cv::Mat rightImage, const DisparityMapParameters*  param, StereoMode mode)
{
    //mode = StereoMode::STEREO_MODE_BM_GPU;

    CPUImage = cv::Mat(leftImage.size(), CV_8U);
    cv::Mat lImage;
    cv::Mat rImage;

    cv::cvtColor(leftImage, lImage, CV_BGR2GRAY);
    cv::cvtColor(rightImage, rImage, CV_BGR2GRAY);

    switch(mode)
    {
        case StereoMode::STEREO_MODE_BM:
        {
            cv::StereoBM sbm;

            if(param)
            {
                sbm.state->preFilterType = param->getPreFilterType();
                sbm.state->preFilterSize = param->getPrefilterSize();
                sbm.state->preFilterCap = param->getPreFilterCap();
                sbm.state->SADWindowSize = param->getSADWindowSize();
                sbm.state->minDisparity = param->getMinDisparity();
                sbm.state->numberOfDisparities = param->getNumberOfDisparities();
                sbm.state->textureThreshold = param->getTextureThreshold();
                sbm.state->uniquenessRatio = param->getUniquenessRatio();
                sbm.state->speckleWindowSize = param->getSpeckleWindowSize();
                sbm.state->speckleRange = param->getSpeckleRange();
                sbm.state->disp12MaxDiff = param->getDisp12MaxDiff();
            }
            else
            {
                sbm.state->preFilterType = cv::StereoBM::BASIC_PRESET;
                sbm.state->preFilterSize = 9;
                sbm.state->preFilterCap = 31;
                sbm.state->SADWindowSize = 21;
                sbm.state->minDisparity = 0;
                sbm.state->numberOfDisparities = 64;
                sbm.state->textureThreshold = 10;
                sbm.state->uniquenessRatio = 15;
                sbm.state->speckleWindowSize = 0;
                sbm.state->speckleRange = 0;
                sbm.state->disp12MaxDiff = -1;
            }

            sbm(lImage, rImage, CPUImage);
            CPUImage.convertTo(CPUImage, CV_8U, 255.0 / (sbm.state->numberOfDisparities * 16.0));

            break;
        }

        case StereoMode::STEREO_MODE_SGBM:
        {
            cv::StereoSGBM sgbm;

            if(param)
            {
                sgbm.minDisparity = param->getMinDisparity();
                sgbm.numberOfDisparities = param->getNumberOfDisparities();
                sgbm.SADWindowSize = param->getSADWindowSize();
                sgbm.preFilterCap = param->getPreFilterCap();
                sgbm.uniquenessRatio = param->getUniquenessRatio();
                sgbm.P1 = 8 * sgbm.SADWindowSize * sgbm.SADWindowSize;
                sgbm.P2 = 32 * sgbm.SADWindowSize * sgbm.SADWindowSize;
                sgbm.speckleWindowSize = param->getSpeckleWindowSize();
                sgbm.speckleRange = param->getSpeckleRange();
                sgbm.disp12MaxDiff = param->getDisp12MaxDiff();
                sgbm.fullDP = param->getFullDP();
            }
            else
            {
                sgbm.minDisparity = 0;
                sgbm.numberOfDisparities = 64;
                sgbm.SADWindowSize = 21;
                sgbm.preFilterCap = 9;
                sgbm.uniquenessRatio = 15;
                sgbm.P1 = 8 * sgbm.SADWindowSize * sgbm.SADWindowSize;
                sgbm.P2 = 32 * sgbm.SADWindowSize * sgbm.SADWindowSize;
                sgbm.speckleWindowSize = 0;
                sgbm.speckleRange = 0;
                sgbm.disp12MaxDiff = -1;
                sgbm.fullDP = false;
            }

            sgbm(lImage, rImage, CPUImage);
            CPUImage.convertTo(CPUImage, CV_8U, 255.0 / (sgbm.numberOfDisparities * 16.0));

            break;
        }

        case StereoMode::STEREO_MODE_BM_GPU:
        {
            cv::gpu::StereoBM_GPU gpubm;
            cv::gpu::GpuMat dispLeft;
            cv::gpu::GpuMat dispRight;
            GPUImage = cv::gpu::GpuMat(lImage.size(), CV_8U);

            if(param)
            {
                gpubm.preset = param->getPreFilterType();
                gpubm.ndisp = param->getNumberOfDisparities();
                gpubm.winSize = param->getSADWindowSize();
                gpubm.avergeTexThreshold = param->getAverageTextureThreshold();
            }
            else
            {
                gpubm.preset = cv::gpu::StereoBM_GPU::BASIC_PRESET;
                gpubm.ndisp = cv::gpu::StereoBM_GPU::DEFAULT_NDISP;
                gpubm.winSize = cv::gpu::StereoBM_GPU::DEFAULT_WINSZ;
                gpubm.avergeTexThreshold = 0.0f;
            }

            dispLeft.upload(lImage);
            dispRight.upload(rImage);

            gpubm(dispLeft, dispRight, GPUImage);
            GPUImage.download(CPUImage);

            break;
        }
    }

    return CPUImage;
}

const cv::Mat& ImageProcessor::depthMap(const cv::Mat& leftImage, const cv::Mat& rightImage, const DisparityMapParameters* param, StereoMode mode)
{
    return CPUImage;
}

cv::Mat ImageProcessor::flann(const cv::Mat& leftImage, const cv::Mat rightImage)
{
    int minHessian = 400;

    cv::SurfFeatureDetector detector (minHessian);
    std::vector<cv::KeyPoint> keypoints_1, keypoints_2;

    detector.detect( rightImage, keypoints_1 );
    detector.detect( leftImage, keypoints_2 );

    cv::SurfDescriptorExtractor extractor;
    cv::Mat descriptors_1, descriptors_2;

    extractor.compute(rightImage, keypoints_1, descriptors_1);
    extractor.compute(leftImage, keypoints_2, descriptors_2);

    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch> matches;

    matcher.match(descriptors_1, descriptors_2, matches);

    double max_dist = 0;
    double min_dist = 100;
    double dist;

    for (int i=0; i<descriptors_1.rows; i++)
    {
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
    drawMatches(rightImage, keypoints_1, leftImage, keypoints_2,
                good_matches, img, cv::Scalar::all(-1), cv::Scalar::all(-1),
                std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    return img;
}
