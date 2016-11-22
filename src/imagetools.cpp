#include "imagetools.hpp"

static ImageTools getInstance() {
  if (singleton == NULL)
    singleton = new ImageTools();

  return singleton;
}

QImage ImageTools::cvMatToImage(const cv::Mat& inMat) {
  //TODO Implement cvmattoimage
}

cv::Mat ImageTools::imageToMat(QImage const& img) {
  //TODO Implement imagetocvmat
}

void split(const cv::Mat& input, cv::Mat& outputLeft, cv::Mat& outputRight) {
  //TODO Implement split 
}
void blur(cv::Mat& image) {
  //TODO Implement blur
}
void sobel(cv::Mat& image) {
  //TODO Implement sobel 
}
void canny(cv::Mat& image) {
  //TODO Implement canny 
}

/*******
  Privé
*******/

ImageTools::ImageTools() {}