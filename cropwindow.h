#ifndef CROPWINDOW_H
#define CROPWINDOW_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QResizeEvent>
#include <QRect>


class CropWindow : public QWidget {
    Q_OBJECT

public:
    CropWindow(const QImage *img);

protected:
    void resizeEvent(QResizeEvent* event);
    void resizeImage();

private:
    QImage img_;
    QLabel *imgLabel_;
    QRect selectedArea_;
};

#endif
