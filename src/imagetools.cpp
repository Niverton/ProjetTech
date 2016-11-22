#include "imagetools.hpp"


static QImage ImageTools::cvMatToImage(const cv::Mat& inMat) {
  //TODO Implement cvmattoimage
}

static cv::Mat ImageTools::imageToMat(QImage const& img) {
  //TODO Implement imagetocvmat
}

static void split(const cv::Mat& input, cv::Mat& outputLeft, cv::Mat& outputRight) {
  //TODO Implement split 
}
static void blur(cv::Mat& image) {
  //TODO Implement blur
}
static void sobel(cv::Mat& image) {
  //TODO Implement sobel 
}
static void canny(cv::Mat& image) {
  //TODO Implement canny 
}