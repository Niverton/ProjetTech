#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H
#define NON_FREE 0 // 0(false) 1(true)

#include <QImage>
#include <opencv2/core/core.hpp>

/*!
 * \brief This is a singleton. Use getInstance()
 */
class ImageTools {
  public:
    /*!
     * \brief Gets the single instance of this class
     */
    static ImageTools& getInstance() {
      static ImageTools instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
      return instance;
    } //Do not implement
    ImageTools(ImageTools const&)     = delete;
    void operator=(ImageTools const&) = delete;

    /*!
     * \brief Converts an opencv Mat object into a QImage.
     * \param inMat: Mat object that has to be converted.
     * \return A QImage corresponding to an opencv Mat image representation.
     */
    QImage cvMatToImage(const cv::Mat& inMat);

    /*!
     * \brief Converts a QImage into an opencv Mat object.
     * \param img: QImage that has to be converted.
     * \return An opencv Mat object corresponding to a QImage image representation.
     */
    cv::Mat imageToMat(QImage const& img);

    /*!
     * \brief Splits an image verticaly
     * \param input: Mat to split
     * \param outputLeft: Left half of the image
     * \param outputRight: Right half of the image     
     */
    void split(const cv::Mat& input, cv::Mat& outputLeft, cv::Mat& outputRight);

    //TODO: Document blur
    void blur(cv::Mat& image, int kernel_size);

    //TODO Document sobel
    void sobel(cv::Mat& image, int kernel_size, int scale);

    //TODO Document canny
   void canny(cv::Mat& image, int kernel_size, double threshold, int ratio);
   
   cv::Mat disparityMapBM(cv::Mat& img_droite, cv::Mat& img_gauche);
  private:
    // Private constructors, do not implement
    ImageTools() {}
};

#endif // IMAGE_TOOLS
