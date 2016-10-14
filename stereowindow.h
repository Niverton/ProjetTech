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
    QImage _imgLeft;
    QImage _imgRight;
    QLabel *_imgLabelLeft;
    QLabel *_imgLabelRight;
};

#endif
