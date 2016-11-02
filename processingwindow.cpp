#include "processingwindow.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdlib.h>

ProcessingWindow::ProcessingWindow(QImage* img){
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("Rogner l'image");

  _img = img->copy(0,0, img->width(), img->height());
  _imgLabel = new QLabel(this);
  _imgLabel->setPixmap(QPixmap::fromImage(_img));

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(_imgLabel);

  setLayout(layout);
  adjustSize();
}

void ProcessingWindow::blur(int kernel_size){
  cv::Mat src = QImage2Mat(_img);
  cv::Mat dst = src.clone();
  cv::blur(src, dst, cv::Size(kernel_size, kernel_size));
  _img = Mat2QImage(dst);
  _imgLabel->setPixmap(QPixmap::fromImage(_img));
}

void ProcessingWindow::sobel(int kernel_size=3, int scale=1){
  cv::Mat src = QImage2Mat(_img);
  cv::Mat dst;
  cv::Sobel(src, dst, src.depth(), 1, 0, kernel_size, scale);
  _img = Mat2QImage(dst);
  _imgLabel->setPixmap(QPixmap::fromImage(_img));
}

void ProcessingWindow::canny(int kernel_size, double threshold, int ratio){
  cv::Mat src = QImage2Mat(_img);

  cv::Mat gray, edge, dst;
  cv::cvtColor(src, gray, CV_BGR2GRAY);
  cv::Canny( gray, edge, threshold, threshold*ratio, kernel_size);
  edge.convertTo(dst, CV_8U);
  cv::cvtColor(dst, dst, CV_GRAY2BGR);
  _img=Mat2QImage(dst);
   _imgLabel->setPixmap(QPixmap::fromImage(_img));
}

QImage ProcessingWindow::Mat2QImage(cv::Mat const& src)
{
  cv::Mat rgb;
  cv::cvtColor(src, rgb, CV_BGR2RGB);
  return QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, QImage::Format_RGB888);
}

cv::Mat ProcessingWindow::QImage2Mat(QImage const& src)
{
  cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
  cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
  int from_to[] = {0,0,1,1,2,2};
  cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
  return mat2;
}
