#include "imagetools.hpp"
#include <opencv2/core/core.hpp>

#define EXPORT __attribute__((visibility("default")))

/* 
Cette lib utilise des cv::Mat non compatible avec unity.
Il faut récupérer la texture opengl liée au renderTexture des deux cameras dans unity, 
puis la convertir en cv::Mat.
*/

extern "C" {
    EXPORT void split(const cv::Mat& input, cv::Mat& outputLeft, cv::Mat& outputRight){
        ImageTools& tools = ImageTools::getInstance();
        tools.split(input, outputLeft, outputRight);
    }

    EXPORT void blur(cv::Mat& image, int kernel_size){
        ImageTools& tools = ImageTools::getInstance();
        tools.blur(image, kernel_size);
    }

    EXPORT void sobel(cv::Mat& image, int kernel_size, int scale){
        ImageTools& tools = ImageTools::getInstance();
        tools.sobel(image, kernel_size, scale);
    }

    EXPORT void canny(cv::Mat& image, int kernel_size, double threshold, int ratio){
        ImageTools& tools = ImageTools::getInstance();
        tools.canny(image, kernel_size, threshold, ratio);
    }

    //mode
    //STEREO_BM: 0
    //STEREO_SGBM: 1
    EXPORT cv::Mat disparityMap(cv::Mat& img_droite, cv::Mat& img_gauche, int mode){
        ImageTools& tools = ImageTools::getInstance();
        tools.disparityMap(img_droite, img_gauche, mode);
    }

    EXPORT void calibrateStereoCamera(cv::Mat& img_gauche, cv::Mat& img_droite){
        ImageTools& tools = ImageTools::getInstance();
        tools.calibrateStereoCamera(img_gauche, img_droite);
    }
}