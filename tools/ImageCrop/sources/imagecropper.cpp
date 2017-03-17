#include "imagecropper.h"

#include <sys/stat.h>
#include <errno.h>

#include <vector>
#include <iostream>

#include <opencv2/opencv.hpp>

ImageCropper::ImageCropper() : 
    count(0) 
{

}

ImageCropper::ImageCropper(const cv::Rect& roi) : 
    count(0),
    roi(roi)
{

}

ImageCropper::ImageCropper(const std::string& inputPath) : 
    count(0),
    baseName(inputPath.substr(inputPath.find_last_of('/') + 1, inputPath.size() - 1))
{
    image = cv::imread(inputPath);
}

ImageCropper::ImageCropper(const std::string& inputPath, const cv::Rect& roi) :
    count(0),
    baseName(inputPath.substr(inputPath.find_last_of('/') + 1, inputPath.size() - 1)),
    roi(roi)
{
    image = cv::imread(inputPath);
}

ImageCropper::~ImageCropper() {}

void ImageCropper::setBaseName(const std::string& string)
{
    baseName = string.substr(string.find_last_of('/') + 1, string.size() - 1);
}

void ImageCropper::setROI(int x, int y, int w, int h)
{
    roi = cv::Rect(x, y, w, h);
}

void ImageCropper::setROI(const cv::Rect& roi)
{
    this->roi = cv::Rect(roi);
}

void ImageCropper::createDirectory() const
{
    if(mkdir("./out/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        std::cerr << strerror(errno) << "\n"; 
        std::exit(-1);
    }
}

void ImageCropper::load(const std::string& inputPath)
{
    baseName = inputPath.substr(inputPath.find_last_of('/') + 1, inputPath.size() - 1);
    image = cv::imread(inputPath);
}

void ImageCropper::save()
{    
    std::string out = std::string("./out/" + baseName);
    image = image(roi);
    cv::imwrite(out, image);
    count++;
}

std::size_t ImageCropper::getCount() const
{
    return count;
}

