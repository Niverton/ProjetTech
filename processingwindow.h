#ifndef PROCESSING_H
#define PROCESSING_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QResizeEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QHBoxLayout>

class ProcessingWindow : public QWidget {
    Q_OBJECT

public:
    ProcessingWindow(QImage* img);

    void blur(int kernel_size);
    void sobel(int kernel_size, int scale);
    void canny();

private:
    QImage _img;
    QLabel* _imgLabel;


    QImage Mat2QImage(cv::Mat const& src);
    cv::Mat QImage2Mat(QImage const& src);

};

#endif
