#include "imagetools.hpp"

#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/calib3d/calib3d.hpp"
# include "opencv2/features2d/features2d.hpp"

#include <opencv2/highgui/highgui.hpp>

#if NON_FREE == 1
    # include "opencv2/nonfree/features2d.hpp"
#endif


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
    cv::Mat disp16 = cv::Mat(img_gauche.rows, img_gauche.cols, CV_16S);
    cv::Mat disp8 = cv::Mat(img_gauche.rows, img_gauche.cols, CV_8UC1);
    cv::Mat img_g, img_d;

    cv::cvtColor(img_gauche, img_g, CV_BGR2GRAY);
    cv::cvtColor(img_droite, img_d, CV_BGR2GRAY);

    int ratio = 7;
    int ndisparities = 16 * ratio;
    int SADWindowSize = 21;
    
    cv::StereoBM sbm = cv::StereoBM(cv::StereoBM::BASIC_PRESET, ndisparities, SADWindowSize );
    sbm( img_g, img_d, disp16, CV_16S );

    double minVal; double maxVal;
    cv::minMaxLoc( disp16, &minVal, &maxVal );

    disp16.convertTo(disp16, CV_8UC1, 255/(maxVal - minVal));
    cv::cvtColor(disp16, disp16, CV_GRAY2BGR);

    cv::normalize(disp16, disp8, 0, 255, CV_MINMAX, CV_8U);

    return disp16;
}


#if NON_FREE == 1
    cv::Mat ImageTools::flann(cv::Mat& img_gauche, cv::Mat img_droite){

        int minHessian = 400;

        cv::SurfFeatureDetector detector (minHessian);
        std::vector<cv::KeyPoint> keypoints_1, keypoints_2;

        detector.detect( img_droite, keypoints_1 );
        detector.detect( img_gauche, keypoints_2 );

        cv::SurfDescriptorExtractor extractor;
        cv::Mat descriptors_1, descriptors_2;
        
        extractor.compute(img_droite, keypoints_1, descriptors_1);
        extractor.compute(img_gauche, keypoints_2, descriptors_2);
    
        cv::FlannBasedMatcher matcher;
        std::vector<cv::DMatch> matches;

        matcher.match(descriptors_1, descriptors_2, matches);
        
        double max_dist = 0; 
        double min_dist = 100;
        double dist;

        for (int i=0; i<descriptors_1.rows; i++){
            dist = matches[i].distance;
            if (dist < min_dist) min_dist = dist;
            if (dist > max_dist) max_dist = dist;
        }

        std::vector<cv::DMatch> good_matches;
        for (int i=0; i<descriptors_1.rows; i++){
            if (matches[i].distance <= cv::max(2*min_dist, 0.02))
                good_matches.push_back( matches[i]);
        }
        
        cv::Mat img;
        drawMatches( img_droite, keypoints_1, img_gauche, keypoints_2,
                good_matches, img, cv::Scalar::all(-1), cv::Scalar::all(-1),
                std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
        return img;
    }

#endif

cv::Mat ImageTools::depthMap(cv::Mat dispMat, cv::Mat Q){
    cv::Mat depthMat;
    cv::reprojectImageTo3D(dispMat, depthMat, Q, false);

    return depthMat;
}