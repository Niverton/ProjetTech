#include "imagetools.hpp"

#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/calib3d/calib3d.hpp"

#include <opencv2/highgui/highgui.hpp>



QImage ImageTools::cvMatToImage(const cv::Mat& inMat) {
  switch(inMat.type())
      {
          // 8-bits, 4 channels
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

cv::Mat ImageTools::imageToMat(QImage const& src) {
  cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
  cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
  int from_to[] = {0,0,1,1,2,2};
  cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
  return mat2;
}

void ImageTools::split(const cv::Mat& input, cv::Mat& outputLeft, cv::Mat& outputRight) {
  cv::Mat tmp = input(cv::Rect(0,0,input.cols/2, input.rows));
  tmp.copyTo(outputLeft);
  tmp = input(cv::Rect(input.cols/2,0,input.cols/2, input.rows));
  tmp.copyTo(outputRight);
}
void ImageTools::blur(cv::Mat& image, int kernel_size) {
  cv::Mat dst = image.clone();
  cv::blur(image, dst, cv::Size(kernel_size, kernel_size));

  image = dst;
}
void ImageTools::sobel(cv::Mat& image, int kernel_size, int scale) {
  int dx = 1;   //derivate x
  int dy = 0;   //derivate y

  cv::Mat dst = image.clone();
  cv::Sobel(image, dst, image.depth(), dx, dy, kernel_size, scale);

  image = dst;
}
void ImageTools::canny(cv::Mat& image, int kernel_size, double threshold, int ratio) {
  cv::Mat src = image.clone();
  cv::Mat gray, edge, dst;
  cv::cvtColor(src, gray, CV_BGR2GRAY);

  cv::Canny( gray, edge, threshold, threshold * ratio, kernel_size);
  edge.convertTo(dst, CV_8U);
  cv::cvtColor(dst, dst, CV_GRAY2BGR);

  image = dst;
}

cv::Mat ImageTools::disparityMapBM(cv::Mat& img_gauche, cv::Mat& img_droite){
    cv::Mat disp, disp8;
    cv::Mat img_g, img_d;

    cv::cvtColor(img_gauche, img_g, CV_BGR2GRAY);
    cv::cvtColor(img_droite, img_d, CV_BGR2GRAY);

    cv::StereoBM sbm;
    sbm(img_g, img_d, disp);
    
    disp.convertTo(disp, CV_8U);
    cv::cvtColor(disp, disp, CV_GRAY2BGR);

    cv::normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);

    return disp;
}
