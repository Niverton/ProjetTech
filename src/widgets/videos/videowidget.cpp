#include "widgets/videos/videowidget.hpp"

#include "processors/imageprocessor.hpp"

#include "except/filenotfoundexception.hpp"
#include "except/framereadfailureexception.hpp"

VideoWidget::VideoWidget(QWidget* parent) : QLabel(parent) {}

VideoWidget::VideoWidget(const QString& filename, QWidget* parent) : QLabel(parent), filename(filename)
{
    if(!videoCapture.open(filename.toUtf8().constData()))
    {
        std::string err = filename.toUtf8().constData();
        err += " not found!";
        throw FileNotFoundException(err.c_str());
    }

    frameRate = static_cast<int>(videoCapture.get(CV_CAP_PROP_FPS));

    if(!videoCapture.read(frame))
    {
        throw FrameReadFailureException("Cannot read frame!");
    }

    ImageProcessor& ip = ImageProcessor::Instance();
    setPixmap(QPixmap::fromImage(ip.cvMatToImage(frame)));
    adjustSize();
}

VideoWidget::~VideoWidget() {}

bool VideoWidget::loadVideo(const QString& file)
{
    if(!videoCapture.open(file.toUtf8().constData()))
    {
        return false;
    }

    if(!videoCapture.read(frame))
    {
        return false;
    }

    ImageProcessor& ip = ImageProcessor::Instance();
    setPixmap(QPixmap::fromImage(ip.cvMatToImage(frame)));
    adjustSize();

    return true;
}
