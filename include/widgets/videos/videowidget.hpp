#ifndef VIDEOWIDGET_HPP
#define VIDEOWIDGET_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QLabel>

class VideoWidget : public QLabel
{
    Q_OBJECT

public:
    VideoWidget(QWidget* parent = nullptr);
    VideoWidget(const QString& filename, QWidget* parent = nullptr);
    ~VideoWidget();

    bool loadVideo(const QString& file);

private:
    cv::Mat             frame;
    cv::Mat             RGBframe;
    cv::VideoCapture    videoCapture;

    QString             filename;

    int                 frameRate;
};

#endif // VIDEOWIDGET_HPP
