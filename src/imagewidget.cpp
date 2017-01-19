#include "imagewidget.hpp"
#include "imagetools.hpp"

#include <QMouseEvent>
#include <QRubberBand>

#include <opencv2/core/core.hpp>

ImageWidget::ImageWidget(QWidget *parent) : QLabel(parent), isCroping(false), firstPoint(), secondPoint() {
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

void ImageWidget::mousePressEvent(QMouseEvent* ev) {
    // Beginning crop
    if(rect().contains(ev->pos()) && !isCroping && !image.empty()){
        isCroping = true;

        // Getting position
        firstPoint.setX(ev->pos().x());
        firstPoint.setY(ev->pos().y());

        rubberBand->setGeometry(QRect(firstPoint, firstPoint));
        rubberBand->show();
    }
}

void ImageWidget::mouseReleaseEvent(QMouseEvent* ev) {
    if(!isCroping)
        return;
  
    secondPoint.setX((ev->pos().x() > image.cols) ? image.cols : ev->pos().x());
    secondPoint.setY((ev->pos().y() > image.rows) ? image.rows : ev->pos().y());
    rubberBand->hide();

    // inclomplet.
    if(firstPoint != secondPoint){
        if(rect().contains(ev->pos())){
            cropImage();
        }
    }

    isCroping = false;
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event) {
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
  setImage(cropped.clone());
  adjustSize();
  parentWidget()->adjustSize();
}
