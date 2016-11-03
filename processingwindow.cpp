#include "processingwindow.h"
#include "imagetools.h"

#include <QLabel>
#include <QHBoxLayout>

ProcessingWindow::ProcessingWindow(const QImage& img, QWidget* parent) : QWidget(parent), _img(img)
{
    if(!parent)
    {
        setAttribute(Qt::WA_DeleteOnClose);
    }

    setWindowTitle("Rogner l'image");

    _imgLabel = new QLabel(this);
    _imgLabel->setPixmap(QPixmap::fromImage(_img));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_imgLabel);

    setLayout(layout);
    adjustSize();
}

void ProcessingWindow::blur(int kernel_size){
    cv::Mat src = ImageTools::image2Mat(_img);
    cv::Mat dst = src.clone();

    cv::blur(src, dst, cv::Size(kernel_size, kernel_size));

    _img = ImageTools::cvMatToImage(dst);
    _imgLabel->setPixmap(QPixmap::fromImage(_img));
}

void ProcessingWindow::sobel(int kernel_size, int scale){
    cv::Mat src = ImageTools::image2Mat(_img);
    cv::Mat dst;

    cv::Sobel(src, dst, src.depth(), 1, 0, kernel_size, scale);

    _img = ImageTools::cvMatToImage(dst);
    _imgLabel->setPixmap(QPixmap::fromImage(_img));
}

void ProcessingWindow::canny(int kernel_size, double threshold, int ratio){
    cv::Mat src = ImageTools::image2Mat(_img);
    cv::Mat gray, edge, dst;
    cv::cvtColor(src, gray, CV_BGR2GRAY);
    cv::Canny( gray, edge, threshold, threshold * ratio, kernel_size);
    edge.convertTo(dst, CV_8U);
    cv::cvtColor(dst, dst, CV_GRAY2BGR);
    _img = ImageTools::cvMatToImage(dst);
    _imgLabel->setPixmap(QPixmap::fromImage(_img));
}
