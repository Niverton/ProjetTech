#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "imagetools.hpp"

#include <opencv2/core/core.hpp>

#include <QLabel>

class UndoStack;

class QRubberBand;
class QMouseEvent;

/*!
 * \brief Cropable Image Widget
 */
class ImageWidget : public QLabel {
  Q_OBJECT

public:
    ImageWidget(QWidget* parent = nullptr, std::size_t index = 0);

    void addUndoStack(UndoStack* stack);

    cv::Mat getImage();
    void setImage(const cv::Mat& im);

protected:
    //TODO Document
    void mousePressEvent(QMouseEvent* ev);
    //TODO Document
    void mouseReleaseEvent(QMouseEvent* ev);
    //TODO Document
    void mouseMoveEvent(QMouseEvent *event);
    //TODO Document
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

    UndoStack*      undoStack;      /*!<  */
};

#endif // IMAGEWIDGET
