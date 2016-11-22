#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QRubberBand>
#include <QPoint>
#include <QImage>
#include <opencv2/core/core.hpp>

/*!
 * \brief Cropable Image Widget
 */
class ImageWidget : QWidget {
  QObject

  public:
    ImageWidget(QWidget *parent = Q_NULLPTR);
    //TODO Document
    void mousePressEvent(QMouseEvent* ev);
    //TODO Document
    void resizeEvent(QResizeEvent* event);
    //TODO Document
    void resizeImage();
    //TODO Document
    void mouseReleaseEvent(QMouseEvent* ev);
    //TODO Document
    void mouseMoveEvent(QMouseEvent *event);
    //TODO Document
    void cropImage();
    //TODO Document
    void resizeEvent(QResizeEvent* event);
    //TODO Document
    void resizeImage();
    
    cv::Mat getImage();
    void setImage(cv::Mat im);

  private:
    ImageTools* tools = ImageTools.getInstance();
    QLabel* label;
    cv::Mat image;
    //Selection
    QRubberBand* rubberBand;
    QPoint firstPoint;
    QPoint secondPoint;
};

#endif // IMAGEWIDGET