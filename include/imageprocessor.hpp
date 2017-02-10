/*!
 * \file imageprocessor.hpp
 * \brief Header containing the declaration of the ImageProcessor class which is used to perform transformation on images.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.1
 */

#ifndef IMAGEPROCESSOR_HPP
#define IMAGEPROCESSOR_HPP

#define NON_FREE 0 // 0(false) 1(true)

#include <QImage>

#include <opencv2/core/core.hpp>

/*!
 * \class ImageProcessor
 * \brief The ImageProcessor class allows to perform several image transformations.
 *        Among these, we can distinguish:
 *          - The ability to split an image. This is useful for stereo images.
 *          - The ability to blur an image.
 *          - The ability to apply a sobel filter to an image.
 *          - The ability to apply a canny filter to an image.
 *          - The ability to produce a disparity map from a stereo image.
 *          - The ability to convert OpenCV Mat object into QImage and vice versa.
 *        The ImageProcessor class is a singleton. As such, using the Instance method in order
 *        to get an instance of the object is mandatory.
 */
class ImageProcessor
{
public:
    /*!
     * \enum StereoMode
     * \brief Enum used to select algorithm for stereo image computation.
     */
    enum StereoMode
    {
        STEREO_MODE_BM = 0,     /*!< Allows to compute stereo correspondence using the block matching algorithm. */
        STEREO_MODE_SGBM        /*!< Semi-global Matching and Mutual Information algorithm. */
    };

public:
    /*!
     * \brief Gets an instance of this class.
     * \return
     */
    static ImageProcessor& Instance()
    {
        static ImageProcessor ip;
        return ip;
    }

    /*!
     * \brief Explicitly tells the compiler to not generate a copy constructor.
     */
    ImageProcessor(ImageProcessor const&) = delete;

    /*!
     * \brief Explicitly tells the compiler to not generate an affectation overload.
     */
    void operator=(ImageProcessor const&) = delete;

    /*!
     * \brief Converts an OpenCV Mat object into a QImage.
     * \param image OpenCV Mat object that has to be converted.
     * \return A QImage object corresponding to an OpenCV image representation.
     * \warning An empty image is returned if the type (channels) of the processed
     *          image is not supported.
     */
    QImage cvMatToImage(const cv::Mat& image);

    /*!
     * \brief Converts a QImage object into an opencv Mat object.
     * \param image QImage object that has to be converted.
     * \return An opencv Mat object corresponding to a QImage image representation.
     */
    cv::Mat imageToCvMat(const QImage& image);

    /*!
     * \brief Splits an image verticaly.
     * \param input         OpenCV representation of an image which has to be to splitted.
     * \param outputLeft    Left half of the image
     * \param outputRight   Right half of the image
     */
    void split(const cv::Mat& input, cv::Mat& outputLeft, cv::Mat& outputRight);

    /*!
     * \brief Applies a blur filter to an image.
     * \param image         Image which has to be blurred.
     * \param kernelSize   Blurring kernel size.
     */
    void blur(cv::Mat& image, int kernelSize);

    /*!
     * \brief Applies a sobel filter to an image.
     *        The Sobel operator, sometimes called the Sobel–Feldman operator or Sobel filter,
     *        is used in image processing and computer vision, particularly within edge
     *        detection algorithms where it creates an image emphasising edges.
     * \param image         Image on which a sobel filter has to be applied.
     * \param kernelSize    Sobel filter kernel size.
     * \param scale         Scale factor.
     */
    void sobel(cv::Mat& image, int kernelSize, int scale);

    /*!
     * \brief Applies a canny filter to an image.
     *        The Canny edge detector is an edge detection operator that uses a multi-stage
     *        algorithm to detect a wide range of edges in images.
     * \param image         Image on which a canny filter has to be applied.
     * \param kernelSize    Canny filter kernel size.
     * \param threshold     First Threshold for the hysteresis procedure.
     * \param ratio         Second threshold ratio for the hysteresis procedure.
     */
    void canny(cv::Mat& image, int kernelSize, double threshold, int ratio);

    /*!
     * \brief Processes the disparity map from a stereo image.
     *        Disparity refers to the difference in location of an object in corresponding two
     *        (left and right) images as seen by the left and right eye which is created due to parallax
     *        (eyes’ horizontal separation). The brain uses this disparity to calculate depth information
     *        from the two dimensional images.
     *        In short, The disparity of a pixel is equal to the shift value that leads to minimum
     *        sum-of-squared-differences for that pixel.
     * \param leftImage     Left image.
     * \param rightImage    Right image.
     * \param mode          Selected algorithm.
     * \return A disparity map from a stereo image under the form of an OpenCv image representation.
     */
    cv::Mat disparityMap(cv::Mat& leftImage, cv::Mat& rightImage, StereoMode mode);

#if NON_FREE == 1
    cv::Mat flann(cv::Mat& img_1, cv::Mat img_2);
#endif

private:
    /*!
     * \brief Default constructor.
     */
    ImageProcessor();

    /*!
     * \brief Default destructor.
     */
    ~ImageProcessor();
};

#endif // IMAGE_TOOLS
