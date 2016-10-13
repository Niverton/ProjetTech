#include "cropwindow.h"

#include <QWidget>
#include <QImage>
#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QRubberBand>
#include <stdio.h>

CropWindow::CropWindow(const QImage *img) {
    //On marque la fenêtre pour être supprimée quand elle est fermée
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Rogner l'image");
    // Init variables
    _cropping = false;
    _rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

    img_ = img->copy(0,0, img->width(), img->height());
    imgLabel_ = new QLabel(this);
    imgLabel_->setPixmap(QPixmap::fromImage(img_));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(imgLabel_);

    setLayout(layout);
    adjustSize();
}

/************
*   resizeEvent
*/
void CropWindow::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    resizeImage();
}

/***********
*   Resize image to fit the window
*/
void CropWindow::resizeImage(){
  QPixmap pxM = QPixmap::fromImage(img_);
  QPixmap* pxmA = const_cast<QPixmap*>(imgLabel_->pixmap());
  QPixmap pxmB = pxM.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  pxmA->swap(static_cast<QPixmap&>(pxmB));
}

/***********
 *   MousePress Event
 */
void CropWindow::mousePressEvent(QMouseEvent* ev){
    // Beginning crop
    if(!_cropping){
        _cropping = true;
        // Getting position
        _beginPoint = ev->pos();
        //printf("%d \t %d \n", _beginPoint.x(), _beginPoint.y());

        _rubberBand->setGeometry(QRect(_beginPoint, _beginPoint));
        _rubberBand->show();
    }

}

/***********
 *   MouseRelease Event
 */
void CropWindow::mouseReleaseEvent(QMouseEvent *ev){
    if(_cropping){
        // Getting coordinates of cropping endPoint
        _endPoint = ev->pos();
        // Hiding rubberband
        _rubberBand->hide();
        // If coordinates are set and not equal (not null and a mouse click holding has been made)
        if(!_beginPoint.isNull() && !_endPoint.isNull() && _beginPoint != _endPoint){
            cropImage();
        }
        // Ending cropping
        _cropping = false;
        //printf("%d \t %d \n", _endPoint.x(), _endPoint.y());
    }
}

/***********
 *   MouseMove Event
 */
void CropWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Updating rubberBand if cropping
    if(_cropping){
        _rubberBand->setGeometry(QRect(_beginPoint, event->pos()).normalized());
    }

}

/***********
 *   Function used to crop the image
 */
void CropWindow::cropImage(){
    QPoint origin(
        (_beginPoint.x() < _endPoint.x()) ? _beginPoint.x() : _endPoint.x(), //X
        (_beginPoint.y() < _endPoint.y()) ? _beginPoint.y() : _endPoint.y()  //Y
    );
    QSize size(
        (_beginPoint.x() > _endPoint.x()) ? _beginPoint.x() - origin.x() : _endPoint.x() - origin.x(), //W
        (_beginPoint.y() > _endPoint.y()) ? _beginPoint.y() - origin.y() : _endPoint.y() - origin.y()  //H
    );
    img_ = img_.copy(QRect(origin, size));
    imgLabel_->setPixmap(QPixmap::fromImage(img_));
    adjustSize();
}
