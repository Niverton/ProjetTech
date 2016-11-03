#include "imagetools.h"

QImage ImageTools::cvMatToImage(const cv::Mat& inMat)
{
    switch(inMat.type())
    {
        // 8 bits, 4 channels
        case CV_8UC4:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_ARGB32);

            return image;
        }

        // 8-bit, 3 channels
        case CV_8UC3:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_RGB888 );
            return image.rgbSwapped();
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

            QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Indexed8);
            image.setColorTable(sColorTable);
            return image;
        }
    }

    return QImage();
}

cv::Mat ImageTools::imageToMat(QImage const& src)
{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = {0,0,1,1,2,2};
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    return mat2;
}
