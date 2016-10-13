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
    cropping_ = false;
    rubberBand_ = new QRubberBand(QRubberBand::Rectangle, this);

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
    if(!cropping_){
        cropping_ = true;
        // Getting position
        beginPoint_ = ev->pos();
        //printf("%d \t %d \n", beginPoint_.x(), beginPoint_.y());

        rubberBand_->setGeometry(QRect(beginPoint_, beginPoint_));
        rubberBand_->show();
    }

}

/***********
 *   MouseRelease Event
 */
void CropWindow::mouseReleaseEvent(QMouseEvent *ev){
    if(cropping_){
        // Getting coordinates of cropping endPoint
        endPoint_ = ev->pos();
        // Hiding rubberband
        rubberBand_->hide();
        // If coordinates are set and not equal (not null and a mouse click holding has been made)
        if(!beginPoint_.isNull() && !endPoint_.isNull() && beginPoint_ != endPoint_){
            cropImage();
        }
        // Ending cropping
        cropping_ = false;
        //printf("%d \t %d \n", endPoint_.x(), endPoint_.y());
    }
}

/***********
 *   MouseMove Event
 */
void CropWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Updating rubberBand if cropping
    if(cropping_){
        rubberBand_->setGeometry(QRect(beginPoint_, event->pos()).normalized());
    }

}

/***********
 *   Function used to crop the image
 */
void CropWindow::cropImage(){
    QPoint origin(
        (beginPoint_.x() < endPoint_.x()) ? beginPoint_.x() : endPoint_.x(), //X
        (beginPoint_.y() < endPoint_.y()) ? beginPoint_.y() : endPoint_.y()  //Y
    );
    QSize size(
        (beginPoint_.x() > endPoint_.x()) ? beginPoint_.x() - origin.x() : endPoint_.x() - origin.x(), //W
        (beginPoint_.y() > endPoint_.y()) ? beginPoint_.y() - origin.y() : endPoint_.y() - origin.y()  //H
    );
    img_ = img_.copy(QRect(origin, size));
    imgLabel_->setPixmap(QPixmap::fromImage(img_));
    adjustSize();
}
