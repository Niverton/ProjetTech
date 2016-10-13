#include "stereowindow.h"

#include <QWidget>
#include <QImage>
#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>


/*************
*   Constructor
*/
StereoWindow::StereoWindow(const QImage *img) {
    //On marque la fenêtre pour être supprimée quand elle est fermée
    setAttribute(Qt::WA_DeleteOnClose);

    imgLeft_ = img->copy(0, 0, img->width()/2, img->height());
    imgRight_ = img->copy(img->width()/2, 0, img->width()/2, img->height());

    imgLabelLeft_ = new QLabel(this);
    imgLabelRight_ = new QLabel(this);

    imgLabelLeft_->setPixmap(QPixmap::fromImage(imgLeft_));
    imgLabelRight_->setPixmap(QPixmap::fromImage(imgRight_));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(imgLabelLeft_);
    layout->addWidget(imgLabelRight_);
    this->setLayout(layout);
}

/************
*   resizeEvent
*/
void StereoWindow::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    resizeImages();
}

/***********
*   Resize images to fit the window
*/
void StereoWindow::resizeImages(){

}
