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

void ProcessingWindow::blur(){
  int width = _img.width();
  int height = _img.height();

  cv::Mat src = QImage2Mat(_img);
  cv::Mat dst = src.clone();
  cv::blur(src, dst, cv::Size(15,15), cv::Point(1,1));
  _img = Mat2QImage(dst);
  _imgLabel->setPixmap(QPixmap::fromImage(_img));
}

void ProcessingWindow::sobel(){
  int width = _img.width();
  int height = _img.height();

  cv::Mat src = QImage2Mat(_img);
  cv::Mat dst;

  for (int y=0; y<height-1; y++){
      for (int x=0; x<width-1; x++){
          cv::Sobel(src, dst, src.depth(), x, y);
        }
    }
  _img = Mat2QImage(dst);
}

void ProcessingWindow::canny(){

  int width = _img.width();
  int height = _img.height();


  cv::Mat src = QImage2Mat(_img);
  /*=cv::Mat dst;

  for (int y=0; y<height-1; y++){
      for (int x=0; x<width-1; x++){

        }
    }
  _img = Mat2QImage(dst);*/
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
