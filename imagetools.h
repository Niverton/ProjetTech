#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/imgproc/imgproc.hpp>

#include <QImage>

class ImageTools
{
public:
    static QImage cvMatToImage(const cv::Mat& inMat);
    static cv::Mat image2Mat(QImage const& img);
};

#endif // IMAGEPROCESSOR_H
