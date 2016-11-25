#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "imagetools.hpp"

#include <QWidget>
#include <QLabel>
#include <QRubberBand>
#include <QPoint>
#include <QImage>
#include <opencv2/core/core.hpp>

/*!
 * \brief Cropable Image Widget
 */
class ImageWidget : public QLabel {
  Q_OBJECT

  public:
    ImageWidget(QWidget *parent = nullptr);
    //TODO Document
    void mousePressEvent(QMouseEvent* ev);
    //TODO Document
    void mouseReleaseEvent(QMouseEvent* ev);
    //TODO Document
    void mouseMoveEvent(QMouseEvent *event);
    //TODO Document
    void cropImage();
    /* TODO Plus tard Gaspard
    //TO DO Document
    void resizeEvent(QResizeEvent* event);
    //TO DO Document
    void resizeImage();
    //*/

    //QSize sizeHint() const;
    
    cv::Mat getImage();
    void setImage(const cv::Mat& im);
  private:
    cv::Mat image;
    //Selection
    bool isCroping;
    QRubberBand* rubberBand;
    QPoint firstPoint;
    QPoint secondPoint;
};

#endif // IMAGEWIDGET
