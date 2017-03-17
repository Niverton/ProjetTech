#ifndef DEF_IMAGE_CROPPER_H
#define DEF_IMAGE_CROPPER_H

#include <string>

#include <opencv2/core/core.hpp>

class ImageCropper
{
public:
    ImageCropper();
    ImageCropper(const cv::Rect& roi);
    ImageCropper(const std::string& inputPath);
    ImageCropper(const std::string& inputPath, const cv::Rect& roi);
    ~ImageCropper();

    void setBaseName(const std::string& string);

    void setROI(int x, int y, int w, int h);
    void setROI(const cv::Rect& roi);

    void createDirectory() const;

    void load(const std::string& inputPath);
    void save();

    std::size_t getCount() const;

private:
    std::size_t count;
   
    std::string baseName;
   
    cv::Rect    roi;
    cv::Mat     image;
};

#endif

