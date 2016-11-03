#include "imageprocessor.h"
#include "imagetools.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
