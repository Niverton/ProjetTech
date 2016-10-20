#include "processing_window.h"
#include <opencv2/imgproc/imgproc.hpp>

ProcessingWindow::ProcessingWindow(QImage* img){
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("Rogner l'image");

  _img = img->copy(0,0, img->width(), img->height());
  _imgLabel = new QLabel(this);

  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(_imgLabel);

  setLayout(layout);
  adjustSize();
}

void ProcessingWindow::blur(){
  int width = _img.width();
  int height = _img.height();

  cv::Mat src = QImage2Mat(_img);
  cv::Mat dst;

  for (int y=0; y<height-1; y++){
      for (int x=0; x<width-1; x++){
          cv::blur(src, dst, cv::Size(x,y));
        }
    }
  _img = Mat2QImage(dst);
}

void ProcessingWindow::sobel(){
  /*int width = _img.width();
  int height = _img.height();

  cv::Mat src = QImage2Mat(_img);
  cv::Mat dst;

  for (int y=0; y<height-1; y++){
      for (int x=0; x<width-1; x++){
          cv::Sobel(src, dst, src.depth(), x, y);
        }
    }
  _img = Mat2QImage(dst);*/
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

void ProcessingWindow::show(){
  _imgLabel = new QLabel(this);
  _imgLabel->setPixmap(QPixmap::fromImage(_img));
}

QImage ProcessingWindow::Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

cv::Mat ProcessingWindow::QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}
