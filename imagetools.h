#ifndef IMAGETOOLS_H
#define IMAGETOOLS_H

#include <opencv2/imgproc/imgproc.hpp>

#include <QImage>

class ImageTools
{
public:
    /*!
     * \brief Converts an opencv Mat object into a QImage.
     * \param inMat : Mat object that has to be converted.
     * \return A QImage corresponding to an opencv Mat image representation.
     */
    static QImage cvMatToImage(const cv::Mat& inMat);

    /*!
     * \brief Converts a QImage into an opencv Mat object.
     * \param img : QImage that has to be converted.
     * \return An opencv Mat object corresponding to a QImage image representation.
     */
    static cv::Mat image2Mat(QImage const& img);
};

#endif // IMAGETOOLS_H
