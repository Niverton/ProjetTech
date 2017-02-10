#include "imagetools.hpp"
#include <opencv2/core/core.hpp>
#include <cstring>
#define EXPORT __attribute__((visibility("default")))

extern "C" {

  void cvMat2ByteArray(const cv::Mat& input, byte& output) {}
  void byteArray2cvMat(const byte& input, cv::Mat& output) {}

  
}
