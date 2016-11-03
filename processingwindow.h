#ifndef PROCESSING_H
#define PROCESSING_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QWidget>
#include <QImage>

class QLabel;

class ProcessingWindow : public QWidget {
    Q_OBJECT

public:
    ProcessingWindow(const QImage& img, QWidget* parent = 0);

    void blur(int kernel_size);
    void sobel(int kernel_size, int scale);
    void canny(int kernel_size, double threshold, int ratio);

private:
    QImage  _img;
    QLabel* _imgLabel;
};

#endif
