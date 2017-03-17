/*!
 * \file imagewidget.hpp
 * \brief Header containing the declaration of the StereoImageWidget class which is designed to contain an image.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.2
 */

#ifndef IMAGECROPWIDGET_HPP
#define IMAGECROPWIDGET_HPP

#include "imagewidget.hpp"

class QRubberBand;
class QMouseEvent;
class QWheelEvent;

class ApplicationStates;

/*!
 * \class StereoImageWidget
 * \brief The StereoImageWidget class is used to display an image.
 *        The main purpose of this container is to hold data of an image under the
 *        OpenCV format. The StereoImageWidget object also features crop capabilities.
 *        An UndoStack objet can be added to this container in order to track each
 *        crop operation.
 *        Note that undo operations are meant to be processed by an upper level widget
 *        in the widget tree. As such, if an UndoStack object is used, it must be attached
 *        to the StereoImageWidget object from the widget which handles the undo logic operations.
 * \warning The zoom-in/zoom-out operations has been developed only for Hadrien Decoudras
 *          who has poor quality eyes. This one is conflictiong with undo operations.
 */
class ImageCropWidget : public ImageWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Default constructor.
     * \param parent Parent widget.
     * \param index  Index of the widget.
     */
    ImageCropWidget(QWidget* parent = nullptr, ApplicationStates* states = nullptr, std::size_t index = 0);

    /*!
     * \brief Allows to add an UndoStack object to the container.
     * \param stack UndoStack object allowing to track crop operations.
     */
    void attachApplicationStates(ApplicationStates* appStates);

signals:
    void coordinatesChanged(const QPoint& coord);

protected:
    /*!
     * \brief Reimplemented method used to track mouse movements in order to process
     *        to a crop operation.
     * \param ev Mouse event.
     */
    void mousePressEvent(QMouseEvent* ev);

    /*!
     * \brief Reimplemented method used to track mouse movements in order to process
     *        to a crop operation. This function triggers the cropImage procedure.
     * \param ev Mouse event.
     */
    void mouseReleaseEvent(QMouseEvent* ev);

    /*!
     * \brief Reimplemented method used to track mouse movements in order to process
     *        to a crop operation.
     * \param ev Mouse event.
     */
    void mouseMoveEvent(QMouseEvent* ev);

    /*!
     * \brief Reimplemented method used to zoom an image.
     * \param ev
     */
    void wheelEvent(QWheelEvent* ev);

    /*!
     * \brief Allows to perform zoom-in/zoom-out operations.
     * \param factor Zoom-in/Zoom-out factor.
     */
    void zoom(float factor);

private:
    /*!
     * \brief Crops the image of the container according to the data collected by
     *        the mouse event reimplemented functions.
     */
    void cropImage();

private:
    std::size_t         index;              /*!< Index of the widget. */

    bool                isCropping;         /*!< Indicates if the user is cropping the image of the widget. */

    QRubberBand*        rubberBand;         /*!< Crop indicator. */

    QPoint              firstPoint;         /*!< Start point of the crop operation. */
    QPoint              secondPoint;        /*!< End point of the crop operaton. */

    ApplicationStates*  appStates;          /*! States of images. */
};

#endif // IMAGECROPWIDGET_HPP
