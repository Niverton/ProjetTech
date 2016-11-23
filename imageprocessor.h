#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>

/*!
 * \class ImageProcessor
 * \brief The ImageProcessor class is used to apply some algorithms to an image.
 */
class ImageProcessor
{
public:
    /*!
     * \enum Filter
     * \brief The Filter enum shows all the available filters which can
     *        be applied to an image.
     */
    enum Filter
    {
        FILTER_NONE = 0,    /*!< No filter. */
        FILTER_BLUR,        /*!< Blur filter. */
        FILTER_SOBEL,       /*!< Sobel filter. */
        FILTER_CANNY        /*!< Canny filter. */
    };

public:
    /*!
     * \brief Constructor alloawing to create a ready to use object.
     * \param image : Image to that has be tansformed.
     */
    ImageProcessor(const QImage& image);

    /*!
     * \brief Default destructor.
     */
    ~ImageProcessor();

public:
    /*!
     * \brief Blurs an image.
     * \param kernel_size
     */
    void blur(int kernel_size);

    /*!
     * \brief Applies a sobel filter to an image.
     * \param kernel_size
     * \param scale
     */
    void sobel(int kernel_size, int scale);

    /*!
     * \brief Applies a canny filter to an image.
     * \param kernel_size
     * \param threshold
     * \param ratio
     */
    void canny(int kernel_size, double threshold, int ratio);

    /*!
     * \brief Gets the transformed images.
     * \return A transformed images if an algorithm has been applied.
     */
    const QImage& getImage() const;

    /*!
     * \brief Sets an image that has to be transformed.
     * \param Image that has to be transformed.
     */
    void setImage(const QImage& image);

    void flann(QImage& img_1, QImage& img_2);

private:
    QImage  img_;   /*!< Transformed image. */
};

#endif // IMAGEPROCESSOR_H

