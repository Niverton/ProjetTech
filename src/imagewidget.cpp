#include "imagewidget.hpp"

#include <QRect>
#include <QPoint>
#include <QRubberBand>
#include <QLabel>
#include <opencv2/core/core.hpp>

ImageWidget::ImageWidget(QWidget *parent = Q_NULLPTR) : QWidget(parent) {
  label = new QLabel(this);
  rubberBand = new QRubberBand(this);
}

void ImageWidget::mousePressEvent(QMouseEvent* ev){
    // Beginning crop
    if(!isCroping){
        isCroping = true;
        // Getting position
        firstPoint = ev->pos();

        rubberBand->setGeometry(QRect(firstPoint, firstPoint));
        rubberBand->show();
    }
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *ev){
  /* TODO Reimplement with cv::Mat instead of QImage
    if(isCroping && ev->pos().x() < size().width() && ev->pos().y() < size().height()){
        // Getting coordinates of cropping endPoint
        firstPoint = ev->pos();
        // Hiding rubberband
        rubberBand->hide();
        // If coordinates are set and not equal (not null and a mouse click holding has been made)
        if(!firstPoint.isNull() && !firstPoint.isNull() && firstPoint != firstPoint){
            cropImage();
        }

        // Ending cropping
        isCroping = false;
    }else if(isCroping && ev->pos().x() > image.width() && ev->pos().y() > image.height()){
        firstPoint = QPoint(image.width(), image.height());
        rubberBand->hide();

        if(!firstPoint.isNull() && !firstPoint.isNull() && firstPoint != firstPoint){
            cropImage();
        }

        isCroping = false;
    }
    //*/
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
  // Updating rubberBand if cropping
  if(isCroping)
    rubberBand->setGeometry(QRect(firstPoint, event->pos()).normalized());
}

void ImageWidget::cropImage(){ //TODO
    QPoint origin(
        (firstPoint.x() < firstPoint.x()) ? firstPoint.x() : firstPoint.x(), //X
        (firstPoint.y() < firstPoint.y()) ? firstPoint.y() : firstPoint.y()  //Y
    );
    QSize size(
        (firstPoint.x() > firstPoint.x()) ? firstPoint.x() - origin.x() : firstPoint.x() - origin.x(), //W
        (firstPoint.y() > firstPoint.y()) ? firstPoint.y() - origin.y() : firstPoint.y() - origin.y()  //H
    );
    /* TODO Reimplement with cv::Mat
    image = image.copy(QRect(origin, size));
    label->setPixmap(QPixmap::fromImage(image));
    //*/
    adjustSize();
}