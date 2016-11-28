#include "imagewidget.hpp"

#include "imagetools.hpp"

#include <QRect>
#include <QPoint>
#include <QRubberBand>
#include <QLabel>
#include <QMouseEvent>
#include <opencv2/core/core.hpp>

ImageWidget::ImageWidget(QWidget *parent /*= Q_NULLPTR*/) : QLabel(parent), isCroping(false), firstPoint(), secondPoint() {
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
  if(!isCroping && !image.empty()){
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
        secondPoint = ev->pos();
        // Hiding rubberband
        rubberBand->hide();
        // If coordinates are set and not equal (not null and a mouse click holding has been made)
        if(firstPoint != secondPoint){
            cropImage();
        }

        // Ending cropping
        isCroping = false;
    }else if(isCroping && ev->pos().x() > image.cols && ev->pos().y() > image.rows){
        secondPoint.setX(image.cols);
        secondPoint.setY(image.rows);
        rubberBand->hide();

        if(firstPoint != secondPoint){
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
  if (image.empty())
    return;
  
  QPoint origin(
    (firstPoint.x() < secondPoint.x()) ? firstPoint.x() : secondPoint.x(), //X
    (firstPoint.y() < secondPoint.y()) ? firstPoint.y() : secondPoint.y()  //Y
  );
  QSize size(
    (firstPoint.x() > secondPoint.x()) ? firstPoint.x() - origin.x() : secondPoint.x() - origin.x(), //W
    (firstPoint.y() > secondPoint.y()) ? firstPoint.y() - origin.y() : secondPoint.y() - origin.y()  //H
  );

  cv::Rect selec(origin.x(), origin.y(), size.width(), size.height());
  cv::Mat cropped = image(selec);
  setImage(cropped);
  adjustSize();
  parentWidget()->adjustSize();
}
