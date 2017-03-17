#ifndef APPLICATIONSTATE_HPP
#define APPLICATIONSTATE_HPP

class ImageWidget;

#include <vector>

#include <opencv2/core/core.hpp>

#include <QPixmap>

class ApplicationStates
{
    struct StereoImagesState
    {
        cv::Mat first;
        cv::Mat second;
    };

    struct StatusBarStates
    {
        std::string notification;
    };

public:
    enum States
    {
        STATE_INITIAL = 0,
        STATE_INITIAL_STEREO,
        STATE_TRANSITORY,
        STATE_PREVIOUS
    };

public:
    void store();
    void reverse(States which);

public:
    ApplicationStates();
    ApplicationStates(ImageWidget* initLeft, ImageWidget* initRight);
    ~ApplicationStates();

    void setInitialImages(ImageWidget* initLeft, ImageWidget* initRight);
    void setInitialLeftImage(ImageWidget* initLeft);
    void setInitialRightImage(ImageWidget* initRight);

    void setInitialStereoImages(ImageWidget* initLeft, ImageWidget* initRight);
    void setInitialLeftStereoImage(ImageWidget* initLeft);
    void setInitialRightStereoImage(ImageWidget* initRight);

    void setTransitoryImages(ImageWidget* transitoryLeft, ImageWidget* transitoryRight);
    void setTransitoryLeftStereoImage(ImageWidget* transitoryLeft);
    void setTransitoryRightStereoImage(ImageWidget* transitoryRight);

public:
    void lockTransitoryState(bool value);

private:
    void destroyStereoStates();

private:
    ImageWidget* stereoLeftWidget;
    ImageWidget* stereoRightWidget;

    QPixmap initialLeft;
    QPixmap initialRight;

    cv::Mat initialStereoLeft;
    cv::Mat initialStereoRight;

    cv::Mat transitoryStereoLeft;
    cv::Mat transitoryStereoRight;

    bool lockTransitory;
    bool transitory;

    std::vector<StereoImagesState*> stereoImages;
};

#endif // APPLICATIONSTATE_H
