#ifndef CROPWINDOW_H
#define CROPWINDOW_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QResizeEvent>
#include <QRect>
#include <QRubberBand>


class CropWindow : public QWidget {
    Q_OBJECT

public:
    CropWindow(const QImage *img);

protected:
    void resizeEvent(QResizeEvent* event);
    void resizeImage();
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent *event);
    void cropImage();

private:
    // Cropping state
    bool cropping_;

    // Cropping coordinates
    QPoint beginPoint_;
    QPoint endPoint_;

    // Rubberband visualization
    QRubberBand *rubberBand_;

    QImage img_;
    QLabel *imgLabel_;
};

#endif
