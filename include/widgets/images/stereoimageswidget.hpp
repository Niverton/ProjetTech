#ifndef STEREOIMAGESWIDGET_HPP
#define STEREOIMAGESWIDGET_HPP

#include <QWidget>

class ImageCropWidget;
class ApplicationStates;

class StereoImagesWidget : public QWidget
{
    Q_OBJECT

public:
    StereoImagesWidget(QWidget* parent = nullptr, ApplicationStates* states = nullptr);
    ~StereoImagesWidget();

    ImageCropWidget* getLeftImageWidget() const;
    ImageCropWidget* getRighImageWidget() const;

private:
    ImageCropWidget* stereoImageLeft;     /*!< Left image. */
    ImageCropWidget* stereoImageRight;    /*!< Right image. */
};

#endif // STEREOIMAGESWIDGET_HPP
