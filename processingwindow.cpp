#include "processing_window.h"
#include <opencv2/imgproc/imgproc.hpp>

ProcessingWindow::ProcessingWindow(QImage* img){
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowTitle("Rogner l'image");

  _img = img->copy(0,0, img->width(), img->height());


  QHBoxLayout *layout = new QHBoxLayout(this);
  layout->addWidget(_imgLabel);

  setLayout(layout);
  adjustSize();
}

void ProcessingWindow::Blur(QImage img){
  cv::Mat mat = QImage2Mat(img);

  _img = Mat2QImage(mat);

}

void ProcessingWindow::ImgShow(){
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
