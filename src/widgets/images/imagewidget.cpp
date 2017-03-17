/*!
 * \file imagewidget.cpp
 * \brief Implementation of the methods of the ImageWidget class declared in the imagewidget.hpp header.
 * \author Jérémi Bernard
 *         Benjamin De Pourquery
 *         Rémy Maugey
 *         Hadrien Decoudras
 * \date 2016-09-01
 * \version 0.2
 */

#include "widgets/images/imagewidget.hpp"

#include "processors/imageprocessor.hpp"

#include <QWheelEvent>
#include <QScrollArea>

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
ImageWidget::ImageWidget(QWidget* parent) : QLabel(parent)
{
    undoZoom.attach(this);
}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
ImageWidget::~ImageWidget() {}

/**************************************************************
 **************************************************************
 *
 * Sets an image.
 *
 **************************************************************/
void ImageWidget::setImage(const cv::Mat& im)
{
    setMinimumSize(QSize(0, 0));
    ImageProcessor& ip = ImageProcessor::Instance();
    image = im.clone();
    setPixmap(QPixmap::fromImage(ip.cvMatToImage(image)));
    adjustSize();
}

/**************************************************************
 **************************************************************
 *
 * Gets an image.
 *
 **************************************************************/
cv::Mat ImageWidget::getImage() const
{
    return image;
}

/**************************************************************
 **************************************************************
 *
 * Is empty.
 *
 **************************************************************/
bool ImageWidget::hasImage() const
{
    return (!image.empty());
}

/**************************************************************
 **************************************************************
 *
 * Cleans.
 *
 **************************************************************/
void ImageWidget::clean()
{
    image.release();
}

/**************************************************************
 **************************************************************
 *
 * Wheel move.
 *
 **************************************************************/
void ImageWidget::wheelEvent(QWheelEvent* ev)
{
    if(!image.empty() && ev->modifiers() == Qt::ControlModifier)
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
 * Zoom in.
 *
 **************************************************************/
void ImageWidget::zoomIn()
{
    zoom(1.10f);
}

/**************************************************************
 **************************************************************
 *
 * Zoom out.
 *
 **************************************************************/
void ImageWidget::zoomOut()
{
    if(!undoZoom.empty())
    {
        zoom(0.90f);
    }
}

/**************************************************************
 **************************************************************
 *
 * zoom.
 *
 **************************************************************/
void ImageWidget::zoom(float factor)
{
    if(factor > 1.0f)
    {
        undoZoom.push(image);

        QPixmap pMap = pixmap()->scaled(QSize(image.cols * factor, image.rows * factor), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        setPixmap(pMap);

        ImageProcessor& tools = ImageProcessor::Instance();
        image = tools.imageToCvMat(pMap.toImage());
    }
    else
    {
        undoZoom.undo();
    }

    adjustSize();
}
