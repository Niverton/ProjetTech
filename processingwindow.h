#ifndef PROCESSINGWINDOW_H
#define PROCESSINGWINDOW_H

#include "imageprocessor.h"

#include <QWidget>
#include <QImage>

class QLabel;

class ProcessingWindow : public QWidget {
    Q_OBJECT

public:
    ProcessingWindow(const QImage& img, ImageProcessor::Filter filter = ImageProcessor::Filter::FILTER_NONE, QWidget* parent = 0);

    void processImage();

private:
    ImageProcessor::Filter  filter_;
    ImageProcessor          imageProcessor_;

    QLabel*                 imgLabel_;
};

#endif
