/*!
 * \file imagewidget.hpp
 * \brief Header containing the declaration of the ImageWidget class which is used to display an image.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.2
 */

#ifndef IMAGEWIDGET_HPP
#define IMAGEWIDGET_HPP

#include "undostack.hpp"

#include <QLabel>

/*!
 * \class ImageWidget
 * \brief The ImageWidget class is used to display an image.
 *        This class features zoom functionalities.
 */
class ImageWidget : public QLabel
{
    Q_OBJECT

public:
    /*!
     * \brief Default costructor.
     * \param parent Parent widget.
     */
    ImageWidget(QWidget* parent = nullptr);

    /*!
     * \brief Default destructor.
     */
    ~ImageWidget();

    /*!
     * \brief Gets the image of the container under the form of a OpenCV Mat object.
     * \return The image of the container under the form of a OpenCV Mat object.
     */
    cv::Mat getImage();

    /*!
     * \brief Sets the image of the container.
     * \param im : OpenCV representation of an image that has to be set.
     */
    void setImage(const cv::Mat& im);

    /*!
     * \brief Determines if the widget has an image.
     * \return True if the widget contains an image; false otherwise.
     */
    bool hasImage() const;

    /*!
     * \brief Removes an image from the widget.
     */
    void clean();

protected:
    /*!
     * \brief Reimplemented method used to zoom an image.
     * \param ev Mouse wheel event.
     */
    void wheelEvent(QWheelEvent* ev);

    /*!
     * \brief Allows to perform zoom-in/zoom-out operations.
     * \param factor Zoom-in/Zoom-out factor.
     */
    virtual void zoom(float factor);

protected slots:
    /*!
     * \brief Allows to perform zoom-in operations.
     */
    void zoomIn();

    /*!
     * \brief Allows to perform zoom-out operations.
     */
    void zoomOut();

protected:
    cv::Mat             image;              /*!< Image. */
    UndoStack           undoZoom;           /*!< Allows to perform zoom-in/zoom-out operations. */
};

#endif // IMAGEWIDGET_H
