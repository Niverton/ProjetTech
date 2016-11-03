#include "processingwindow.h"

#include <QLabel>
#include <QHBoxLayout>

ProcessingWindow::ProcessingWindow(const QImage& img, ImageProcessor::Filter filter, QWidget* parent) : QWidget(parent), filter_(filter), imageProcessor_(img)
{
    if(!parent)
    {
        setAttribute(Qt::WA_DeleteOnClose);
    }

    setWindowTitle("Rogner l'image");

    imgLabel_ = new QLabel(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(imgLabel_);

    setLayout(layout);
    adjustSize();
}

void ProcessingWindow::processImage()
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
