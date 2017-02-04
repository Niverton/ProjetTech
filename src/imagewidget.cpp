/*!
 * \file imagewidget.cpp
 * \brief Implementation of the methods of the ImageWidget class declared in the imagewidget.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \version 0.2
 */

#include "imagewidget.hpp"
#include "imagetools.hpp"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QRubberBand>


/**************************************************************
 **************************************************************
 *
 * Constructor
 *
 **************************************************************/
ImageWidget::ImageWidget(QWidget *parent, std::size_t index) :
    QLabel(parent), index(index), isCropping(false), firstPoint(), secondPoint(), undoStack(nullptr) {
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

    if(index == 0){
        undoZoom.setLeftWidget(this);
    }else{
        undoZoom.setRightWidget(this);
    }
}

/**************************************************************
 **************************************************************
 *
 * Adds undo manager.
 *
 **************************************************************/
void ImageWidget::addUndoStack(UndoStack* stack){
    undoStack = stack;
}

/**************************************************************
 **************************************************************
 *
 * Sets an image.
 *
 **************************************************************/
void ImageWidget::setImage(const cv::Mat& im) {
    setMinimumSize(QSize(0, 0));
    ImageTools& tools = ImageTools::getInstance();
    image = im.clone();
    setPixmap(QPixmap::fromImage(tools.cvMatToImage(image)));
    adjustSize();
}

/**************************************************************
 **************************************************************
 *
 * Gets an image.
 *
 **************************************************************/
cv::Mat ImageWidget::getImage() {
  return image.clone();
}

/**************************************************************
 **************************************************************
 *
 * Mouse press.
 *
 **************************************************************/
void ImageWidget::mousePressEvent(QMouseEvent* ev) {
    // Beginning crop
    if(rect().contains(ev->pos()) && !isCropping && !image.empty()){
        isCropping = true;

        // Getting position
        firstPoint.setX(ev->pos().x());
        firstPoint.setY(ev->pos().y());

        rubberBand->setGeometry(QRect(firstPoint, firstPoint));
        rubberBand->show();
    }
}

/**************************************************************
 **************************************************************
 *
 * Mouse release.
 *
 **************************************************************/
void ImageWidget::mouseReleaseEvent(QMouseEvent* ev) {
    if(!isCropping)
        return;
  
    secondPoint.setX((ev->pos().x() > image.cols) ? image.cols : ev->pos().x());
    secondPoint.setY((ev->pos().y() > image.rows) ? image.rows : ev->pos().y());
    rubberBand->hide();

    if(firstPoint != secondPoint){
        if(rect().contains(ev->pos())){
            if(undoStack != nullptr)
            {
                UndoStack::UndoStackImage op = static_cast<UndoStack::UndoStackImage>(index);

                switch(op){
                    case UndoStack::UndoStackImage::UNDO_STACK_IMAGE_FIRST:{
                        undoStack->pushLeft(image);
                        break;
                    }

                    case UndoStack::UndoStackImage::UNDO_STACK_IMAGE_SECOND:{
                        undoStack->pushRight(image);
                        break;
                    }
                }
            }

            cropImage();
        }
    }

    isCropping = false;
}

/**************************************************************
 **************************************************************
 *
 * Mouse move.
 *
 **************************************************************/
void ImageWidget::mouseMoveEvent(QMouseEvent *ev) {
  // Updating rubberBand if cropping
  if(isCropping)
    rubberBand->setGeometry(QRect(firstPoint, ev->pos()).normalized());
}

void ImageWidget::wheelEvent(QWheelEvent* ev){
    if(ev->modifiers() == Qt::ControlModifier){
        if(ev->delta() > 0){
            zoomIn();
        }else{
            zoomOut();
        }
    }else{
        QLabel::wheelEvent(ev);
    }
}

/**************************************************************
 **************************************************************
 *
 * Crop.
 *
 **************************************************************/
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

/**************************************************************
 **************************************************************
 *
 * Zoom in.
 *
 **************************************************************/
void ImageWidget::zoomIn(){
    zoom(1.10f);
}

/**************************************************************
 **************************************************************
 *
 * Zoom out.
 *
 **************************************************************/
void ImageWidget::zoomOut(){
    if(!undoZoom.isEmpty()){
        zoom(0.90f);
    }
}

/**************************************************************
 **************************************************************
 *
 * zoom.
 *
 **************************************************************/
void ImageWidget::zoom(float factor){
    UndoStack::UndoStackImage op = static_cast<UndoStack::UndoStackImage>(index);

    if(factor > 1.0f){
        switch(op){
            case UndoStack::UndoStackImage::UNDO_STACK_IMAGE_FIRST:{
                undoZoom.pushLeft(image);
                break;
            }

            case UndoStack::UndoStackImage::UNDO_STACK_IMAGE_SECOND:{
                undoZoom.pushRight(image);
                break;
            }
        }

        QPixmap pMap = pixmap()->scaled(QSize(image.cols * factor, image.rows * factor), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        setPixmap(pMap);
        ImageTools& tools = ImageTools::getInstance();
        image = tools.imageToMat(pMap.toImage());
    }else{
        undoZoom.undo();
    }

    adjustSize();
}
