#include "cropwindow.h"

#include <QWidget>
#include <QImage>
#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QRubberBand>

CropWindow::CropWindow(const QImage *img) {
    //On marque la fenêtre pour être supprimée quand elle est fermée
    setAttribute(Qt::WA_DeleteOnClose);

    // Init variables
    _cropping = false;

    img_ = img->copy(0,0, img->width(), img->height());
    imgLabel_ = new QLabel(this);
    imgLabel_->setPixmap(QPixmap::fromImage(img_));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(imgLabel_);
    this->setLayout(layout);
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
        // Creating rubberband
        if(_rubberBand == NULL)
            _rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        _rubberBand->setGeometry(QRect(_beginPoint, QSize()));
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
    img_ = img_.copy(_beginPoint.x(), _beginPoint.y(), _endPoint.x(), _endPoint.y());
    imgLabel_->setPixmap(QPixmap::fromImage(img_));
}
