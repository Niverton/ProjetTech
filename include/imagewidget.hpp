/*!
 * \file imagewidget.hpp
 * \brief Header containing the declaration of the ImageWidget class which is designed
 *        to contain an image.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \version 0.2
 */

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <opencv2/core/core.hpp>

#include <QLabel>

class UndoStack;

class QRubberBand;
class QMouseEvent;

/*!
 * \class ImageWidget
 * \brief The ImageWidget class is used to display an image.
 *        The main purpose of this container is to hold data of an image under the
 *        OpenCV format. The ImageWidget object also features crop capabilities.
 *        An UndoStack objet can be added to this container in order to track each
 *        crop operation.
 *        Note that undo operations are meant to be processed by an upper level widget
 *        in the widget tree. As such, if an UndoStack object is used, it must be attached
 *        to the ImageWidget object from the widget which handles the undo logic operations.
 */
class ImageWidget : public QLabel {
  Q_OBJECT

public:
    /*!
     * \brief Default constructor.
     * \param parent Parent widget.
     * \param index  Index of the widget.
     */
    ImageWidget(QWidget* parent = nullptr, std::size_t index = 0);

    /*!
     * \brief Allows to add an UndoStack object to the container.
     * \param stack UndoStack object allowing to track crop operations.
     */
    void addUndoStack(UndoStack* stack);

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
     * \brief Crops the image of the container according to the data collected by
     *        the mouse event reimplemented functions.
     */
    void cropImage();

    /* TODO Plus tard Gaspard
    //TO DO Document
    void resizeEvent(QResizeEvent* event);
    //TO DO Document
    void resizeImage();
    //*/

    //QSize sizeHint() const;

private:
    std::size_t     index;          /*!< Index of the widget. */

    cv::Mat         image;          /*!< Widget image. */

    bool            isCropping;     /*!< Indicates if the user is cropping the image of the widget. */

    QRubberBand*    rubberBand;     /*!< Crop indicator. */

    QPoint          firstPoint;     /*!< Start point of the crop operation. */
    QPoint          secondPoint;    /*!< End point of the crop operaton. */

    UndoStack*      undoStack;      /*!< UndoStack object of un upper level widget. */
};

#endif // IMAGEWIDGET
