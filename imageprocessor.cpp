#include "imageprocessor.h"
#include "imagetools.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv_modules.hpp"

# include "opencv2/features2d/features2d.hpp"
# include "opencv2/highgui/highgui.hpp"
# include "opencv2/nonfree/features2d.hpp"

/**********************************************************************
 **********************************************************************
 *
 * Ctor
 *
 **********************************************************************/
ImageProcessor::ImageProcessor(const QImage& image) : img_(image) {}

/**********************************************************************
 **********************************************************************
 *
 * Dtor.
 *
 **********************************************************************/
ImageProcessor::~ImageProcessor() {}

/**********************************************************************
 **********************************************************************
 *
 * Blur filter.
 *
 **********************************************************************/
void ImageProcessor::blur(int kernel_size)
{
    cv::Mat src = ImageTools::imageToMat(img_);
    cv::Mat dst = src.clone();

    cv::blur(src, dst, cv::Size(kernel_size, kernel_size));

    img_ = ImageTools::cvMatToImage(dst);
}

/**********************************************************************
 **********************************************************************
 *
 * Sobel filter.
 *
 **********************************************************************/
void ImageProcessor::sobel(int kernel_size, int scale)
{
    cv::Mat src = ImageTools::imageToMat(img_);
    cv::Mat dst;

    cv::Sobel(src, dst, src.depth(), 1, 0, kernel_size, scale);

    img_ = ImageTools::cvMatToImage(dst);
}

/**********************************************************************
 **********************************************************************
 *
 * Canny filter.
 *
 **********************************************************************/
void ImageProcessor::canny(int kernel_size, double threshold, int ratio){
    cv::Mat src = ImageTools::imageToMat(img_);
    cv::Mat gray, edge, dst;
    cv::cvtColor(src, gray, CV_BGR2GRAY);

    cv::Canny( gray, edge, threshold, threshold * ratio, kernel_size);
    edge.convertTo(dst, CV_8U);
    cv::cvtColor(dst, dst, CV_GRAY2BGR);

    img_ = ImageTools::cvMatToImage(dst);
}

/**********************************************************************
 **********************************************************************
 *
 * Get processed image.
 *
 **********************************************************************/
const QImage& ImageProcessor::getImage() const
{
    return img_;
}

/**********************************************************************
 **********************************************************************
 *
 * Set an image to be processed.
 *
 **********************************************************************/
void ImageProcessor::setImage(const QImage& image)
{
    img_ = QImage(image);
}


/*
    3 étapes:
        - Algotithme de surf
        - Créer un descritpeur
        - Matcher les descripteurs avec flann

void ImageProcessor::flann(QImage& img_1, QImage& img_2){

    cv::Mat img_droite = ImageTools::imageToMat(img_1);
    cv::Mat img_gauche = ImageTools::imageToMat(img_2);

    int minHessian = 400;
    cv::SurfFeatureDetector detector( minHessian );
    
    std::vector<cv::KeyPoint> keypoints_1, keypoints_2;
    cv::detector.detect( img_droite, keypoints_1 );
    cv::detector.detect( img_gauche, keypoints_2 );

    //Surf descriptor
    cv::SurfDescriptorExtractor extractor;

    cv::Mat descriptors_1, descriptors_2;

    //Matching descriptor vectors using FLANN matcher

    cv::FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    cv::matcher.match( descriptors_1, descriptors_2, matches );
    img_ = ImageTools::cvMatToImage(matches);
}
*/