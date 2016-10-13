#include "cropwindow.h"

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QResizeEvent>

CropWindow::CropWindow(const QImage *img) {
    //On marque la fenêtre pour être supprimée quand elle est fermée
    setAttribute(Qt::WA_DeleteOnClose);


}

/************
*   resizeEvent
*/
void StereoWindow::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    resizeImage();
}

/***********
*   Resize image to fit the window
*/
void StereoWindow::resizeImage(){

}
