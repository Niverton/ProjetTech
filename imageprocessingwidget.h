#ifndef PROCESSINGWINDOW_H
#define PROCESSINGWINDOW_H

#include "imageprocessor.h"

#include <QWidget>
#include <QImage>

class QLabel;

/*!
 * \class ImageProcessingWidget
 * \brief The ImageProcessingWidget class allows to display an image which is meant
 *        to be transformed or is already transformed.
 *        The whole process of image trasformation is achieved by an ImageProcessor
 *        object.
 */
class ImageProcessingWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor allowing to create a ready to use ImageProcessingWidget object.
     * \param img : Image that has to be transformed.
     * \param filter : Filter which needs to be applied.
     *                 This field will determines the algorithm to run in the processImage
     *                 method.
     * \param parent : Parent widget.
     */
    ImageProcessingWidget(const QImage& img, ImageProcessor::Filter filter = ImageProcessor::Filter::FILTER_NONE, QWidget* parent = 0);

    /*!
     * \brief Run a specific algorithm.
     *        These algorithms are declared in the ImageProcessor class.
     */
    void processImage();

private:
    ImageProcessor::Filter  filter_;            /*!< Filter applied to an image. */
    ImageProcessor          imageProcessor_;    /*!< ImageProcessor object used to run image transformation algorithms. */

    QLabel*                 imgLabel_;          /*!< Image container. */
};

#endif
