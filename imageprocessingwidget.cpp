#include "imageprocessingwidget.h"

#include <QLabel>
#include <QHBoxLayout>

/**********************************************************************
 **********************************************************************
 *
 * Ctor
 *
 **********************************************************************/
ImageProcessingWidget::ImageProcessingWidget(const QImage& img, ImageProcessor::Filter filter, QWidget* parent) : QWidget(parent), filter_(filter), imageProcessor_(img)
{
    if(!parent)
    {
        setAttribute(Qt::WA_DeleteOnClose);

        switch(filter_)
        {
            case ImageProcessor::Filter::FILTER_NONE:
            {
                setWindowTitle("Processing Window - No filter");
                break;
            }

            case ImageProcessor::Filter::FILTER_BLUR:
            {
                setWindowTitle("Processing Window - Blur filter");
                break;
            }

            case ImageProcessor::Filter::FILTER_SOBEL:
            {
                setWindowTitle("Processing Window - Sobel filter");
                break;
            }

            case ImageProcessor::Filter::FILTER_CANNY:
            {
                setWindowTitle("Processing Window - Canny filter");
                break;
            }
        }
    }

    imgLabel_ = new QLabel(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(imgLabel_);

    setLayout(layout);
    adjustSize();
}

/**********************************************************************
 **********************************************************************
 *
 * Image transformation.
 *
 **********************************************************************/
void ImageProcessingWidget::processImage()
{
    switch(filter_)
    {
        case ImageProcessor::Filter::FILTER_NONE:
        {
            break;
        }

        case ImageProcessor::Filter::FILTER_BLUR:
        {
            imageProcessor_.blur(5);
            break;
        }

        case ImageProcessor::Filter::FILTER_SOBEL:
        {
            imageProcessor_.sobel(3, 1);
            break;
        }

        case ImageProcessor::Filter::FILTER_CANNY:
        {
            imageProcessor_.canny(3, 20, 2);
            break;
        }
    }

    imgLabel_->setPixmap(QPixmap::fromImage(imageProcessor_.getImage()));
}
