#include "imagewidget.hpp"

#include "imagetools.hpp"

#include <QRect>
#include <QPoint>
#include <QRubberBand>
#include <QLabel>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>

ImageWidget::ImageWidget(QWidget *parent /*= Q_NULLPTR*/) : QLabel(parent), isCroping(false) {
  rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
}

void ImageWidget::setImage(const cv::Mat& im) {
  ImageTools& tools = ImageTools::getInstance();
  image = im.clone();
  setPixmap(QPixmap::fromImage(tools.cvMatToImage(image)));
  adjustSize();
}

cv::Mat ImageWidget::getImage() {
  return image.clone();
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
    if(isCroping && ev->pos().x() < size().width() && ev->pos().y() < size().height()){
        // Getting coordinates of cropping endPoint
        firstPoint = ev->pos();
        // Hiding rubberband
        rubberBand->hide();
        // If coordinates are set and not equal (not null and a mouse click holding has been made)
        if(!firstPoint.isNull() && !secondPoint.isNull() && firstPoint != secondPoint){
            cropImage();
        }

        // Ending cropping
        isCroping = false;
    }else if(isCroping && ev->pos().x() > image.cols && ev->pos().y() > image.rows){
        firstPoint = QPoint(image.cols, image.rows);
        rubberBand->hide();

        if(!firstPoint.isNull() && !firstPoint.isNull() && firstPoint != firstPoint){
            cropImage();
        }

        isCroping = false;
    }
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
  // Updating rubberBand if cropping
  if(isCroping)
    rubberBand->setGeometry(QRect(firstPoint, event->pos()).normalized());
}

void ImageWidget::cropImage(){
  QPoint origin(
    (firstPoint.x() < firstPoint.x()) ? firstPoint.x() : firstPoint.x(), //X
    (firstPoint.y() < firstPoint.y()) ? firstPoint.y() : firstPoint.y()  //Y
  );
  QSize size(
    (firstPoint.x() > firstPoint.x()) ? firstPoint.x() - origin.x() : firstPoint.x() - origin.x(), //W
    (firstPoint.y() > firstPoint.y()) ? firstPoint.y() - origin.y() : firstPoint.y() - origin.y()  //H
  );

  cv::Rect selec(origin.x(), origin.y(), size.width(), size.height());
  cv::Mat cropped = image(selec);
  setImage(cropped);
  //adjustSize();
}
