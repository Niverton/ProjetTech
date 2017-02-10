/*!
 * \file imagewidget.cpp
 * \brief Implementation of the methods of the StereoImageWidget class declared in the stereoimagewidget.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.2
 */

#include "stereoimagewidget.hpp"
#include "imageprocessor.hpp"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QRubberBand>

/**************************************************************
 **************************************************************
 *
 * Constructor
 *
 **************************************************************/
StereoImageWidget::StereoImageWidget(QWidget* parent, std::size_t index) : ImageWidget(parent), index(index), isCropping(false), undoStack(nullptr)
{
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

    if(index == 0)
    {
        undoZoom.setLeftWidget(this);
    }
    else
    {
        undoZoom.setRightWidget(this);
    }
}

/**************************************************************
 **************************************************************
 *
 * Adds undo manager.
 *
 **************************************************************/
void StereoImageWidget::addUndoStack(UndoStack* stack)
{
    undoStack = stack;
}

#include <QDebug>

/**************************************************************
 **************************************************************
 *
 * Mouse press.
 *
 **************************************************************/
void StereoImageWidget::mousePressEvent(QMouseEvent* ev)
{
    qDebug() << !image.empty();

    // Beginning crop
    if(rect().contains(ev->pos()) && !isCropping && !image.empty())
    {
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
void StereoImageWidget::mouseReleaseEvent(QMouseEvent* ev)
{
    if(!isCropping)
    {
        return;
    }

    secondPoint.setX((ev->pos().x() > image.cols) ? image.cols : ev->pos().x());
    secondPoint.setY((ev->pos().y() > image.rows) ? image.rows : ev->pos().y());
    rubberBand->hide();

    if(firstPoint != secondPoint)
    {
        if(rect().contains(ev->pos()))
        {
            if(undoStack != nullptr)
            {
                UndoStack::StereoUndoStackImage op = static_cast<UndoStack::StereoUndoStackImage>(index);

                switch(op){
                    case UndoStack::StereoUndoStackImage::UNDO_STACK_IMAGE_FIRST:
                    {
                        undoStack->pushLeft(image);
                        break;
                    }

                    case UndoStack::StereoUndoStackImage::UNDO_STACK_IMAGE_SECOND:
                    {
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
void StereoImageWidget::mouseMoveEvent(QMouseEvent *ev)
{
    // Updating rubberBand if cropping
    if(isCropping)
    {
        rubberBand->setGeometry(QRect(firstPoint, ev->pos()).normalized());
    }
}

/**************************************************************
 **************************************************************
 *
 * Wheel move.
 *
 **************************************************************/
void StereoImageWidget::wheelEvent(QWheelEvent* ev)
{
    if(ev->modifiers() == Qt::ControlModifier)
    {
        if(ev->delta() > 0)
        {
            zoomIn();
        }
        else
        {
            zoomOut();
        }
    }
    else
    {
        QLabel::wheelEvent(ev);
    }
}

/**************************************************************
 **************************************************************
 *
 * Crop.
 *
 **************************************************************/
void StereoImageWidget::cropImage()
{
    if(image.empty())
    {
        return;
    }
  
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
}

/**************************************************************
 **************************************************************
 *
 * zoom.
 *
 **************************************************************/
void StereoImageWidget::zoom(float factor)
{
    UndoStack::StereoUndoStackImage op = static_cast<UndoStack::StereoUndoStackImage>(index);

    if(factor > 1.0f)
    {
        switch(op)
        {
            case UndoStack::StereoUndoStackImage::UNDO_STACK_IMAGE_FIRST:
            {
                undoZoom.pushLeft(image);
                break;
            }

            case UndoStack::StereoUndoStackImage::UNDO_STACK_IMAGE_SECOND:
            {
                undoZoom.pushRight(image);
                break;
            }
        }

        QPixmap pMap = pixmap()->scaled(QSize(image.cols * factor, image.rows * factor), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        setPixmap(pMap);
        ImageProcessor& tools = ImageProcessor::Instance();
        image = tools.imageToCvMat(pMap.toImage());
    }
    else
    {
        undoZoom.undo();
    }
}
