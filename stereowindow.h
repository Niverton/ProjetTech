#ifndef STEREOWINDOW_H
#define STEREOWINDOW_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QResizeEvent>


class StereoWindow : public QWidget {
    Q_OBJECT

public:
    StereoWindow(const QImage *img);

protected:
    void resizeEvent(QResizeEvent* event);
    void resizeImages();

private:
    QImage imgLeft_;
    QImage imgRight_;
    QLabel *imgLabelLeft_;
    QLabel *imgLabelRight_;


};

#endif
