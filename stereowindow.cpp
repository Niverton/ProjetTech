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
    setWindowTitle("Couper l'image");
    _imgLeft = img->copy(0, 0, img->width()/2, img->height());
    _imgRight = img->copy(img->width()/2, 0, img->width()/2, img->height());

    _imgLabelLeft = new QLabel(this);
    _imgLabelRight = new QLabel(this);

    _imgLabelLeft->setPixmap(QPixmap::fromImage(_imgLeft));
    _imgLabelRight->setPixmap(QPixmap::fromImage(_imgRight));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(_imgLabelLeft);
    layout->addWidget(_imgLabelRight);
    setLayout(layout);
    adjustSize();
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
