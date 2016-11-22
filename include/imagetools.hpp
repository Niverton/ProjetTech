#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

class ImageTools {
  public:
    /*!
     * \brief Gets the single instance of this class
     */
    static ImageTools getInstance();

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
    void blur(cv::Mat& image);

    //TODO Document sobel
    void sobel(cv::Mat& image);

    //TODO Document canny
    void canny(cv::Mat& image);

  private:
    // Constructeur privé
    ImageTools();
    //Singleton
    ImageTools* singleton = NULL;


};

#endif // IMAGE_TOOLS