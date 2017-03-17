#include "utils/applicationstates.hpp"

#include "widgets/images/imagewidget.hpp"

#include "except/applicationstatesnullstereowidget.hpp"

ApplicationStates::ApplicationStates() : stereoLeftWidget(nullptr), stereoRightWidget(nullptr), lockTransitory(false), transitory(false) {}

ApplicationStates::ApplicationStates(ImageWidget* initlLeft, ImageWidget* initRight) : stereoLeftWidget(initlLeft), stereoRightWidget(initRight), lockTransitory(false), transitory(false)
{
    initialLeft = *(initlLeft->pixmap());
    initialRight = *(initRight->pixmap());
}

ApplicationStates::~ApplicationStates()
{
    destroyStereoStates();
}

void ApplicationStates::setInitialImages(ImageWidget* initLeft, ImageWidget* initRight)
{
    stereoLeftWidget = initLeft;
    stereoRightWidget = initRight;
    initialLeft = *(initLeft->pixmap());
    initialRight = *(initRight->pixmap());
}

void ApplicationStates::setInitialLeftImage(ImageWidget* initLeft)
{
    stereoLeftWidget = initLeft;
    initialLeft = *(initLeft->pixmap());
}

void ApplicationStates::setInitialRightImage(ImageWidget* initRight)
{
    stereoLeftWidget = initRight;
    initialRight = *(initRight->pixmap());
}

void ApplicationStates::setInitialStereoImages(ImageWidget* initLeft, ImageWidget* initRight)
{
    stereoLeftWidget = initLeft;
    stereoRightWidget = initRight;
    initialStereoLeft = initLeft->getImage().clone();
    initialStereoRight = initRight->getImage().clone();
}

void ApplicationStates::setInitialLeftStereoImage(ImageWidget* initLeft)
{
    stereoLeftWidget = initLeft;
    initialStereoLeft = initLeft->getImage().clone();
}

void ApplicationStates::setInitialRightStereoImage(ImageWidget* initRight)
{
    stereoRightWidget = initRight;
    initialStereoRight = initRight->getImage().clone();
}

void ApplicationStates::setTransitoryImages(ImageWidget* transitoryLeft, ImageWidget* transitoryRight)
{
    transitoryStereoLeft = transitoryLeft->getImage().clone();
    transitoryStereoRight = transitoryRight->getImage().clone();
    transitory = true;
}

void ApplicationStates::setTransitoryLeftStereoImage(ImageWidget* transitoryLeft)
{
    transitoryStereoLeft = transitoryLeft->getImage().clone();
    transitory = true;
}

void ApplicationStates::setTransitoryRightStereoImage(ImageWidget* transitoryRight)
{
    transitoryStereoRight = transitoryRight->getImage().clone();
    transitory = true;
}

void ApplicationStates::store()
{
    if(!stereoLeftWidget)
    {
        throw ApplicationStatesNullStereoWidgetException("Left stereo widget is NULL!");
    }

    StereoImagesState* state = nullptr;

    if(stereoLeftWidget->hasImage())
    {
        if(initialStereoLeft.empty())
        {
            initialStereoLeft = stereoLeftWidget->getImage().clone();
        }
        else
        {
            state = new StereoImagesState();
            state->first = stereoLeftWidget->getImage().clone();
        }
    }

    if(stereoRightWidget->hasImage())
    {
        if(initialStereoRight.empty())
        {
            initialStereoRight = stereoRightWidget->getImage().clone();
        }
        else
        {
            state->second = stereoRightWidget->getImage().clone();
        }
    }

    if(state)
    {
        stereoImages.push_back(state);
    }
}

void ApplicationStates::reverse(States which)
{
    switch(which)
    {
        case States::STATE_INITIAL:
        {
            if(!stereoLeftWidget)
            {
                throw ApplicationStatesNullStereoWidgetException("Left stereo widget is NULL!");
            }

            if(!stereoRightWidget)
            {
                throw ApplicationStatesNullStereoWidgetException("Right stereo widget is NULL!");
            }

            destroyStereoStates();
            stereoImages.clear();
            stereoImages.resize(0);
            stereoImages.shrink_to_fit();
            initialStereoLeft.release();
            initialStereoRight.release();

            stereoLeftWidget->setPixmap(initialLeft);
            stereoRightWidget->setPixmap(initialRight);

            break;
        }

        case States::STATE_INITIAL_STEREO:
        {
            if(!stereoLeftWidget)
            {
                throw ApplicationStatesNullStereoWidgetException("Left stereo widget is NULL!");
            }

            if(!stereoRightWidget)
            {
                throw ApplicationStatesNullStereoWidgetException("Right stereo widget is NULL!");
            }

            destroyStereoStates();
            stereoImages.clear();
            stereoImages.resize(0);
            stereoImages.shrink_to_fit();
            stereoLeftWidget->setImage(initialStereoLeft);
            stereoRightWidget->setImage(initialStereoRight);

            break;
        }

        case States::STATE_TRANSITORY:
        {
            if(transitory)
            {
                if(!transitoryStereoRight.empty())
                {
                    stereoLeftWidget->setImage(transitoryStereoLeft);
                    stereoRightWidget->setImage(transitoryStereoRight);
                }
                else
                {
                    stereoLeftWidget->setImage(transitoryStereoLeft);
                }

                break;
            }
        }

        case States::STATE_PREVIOUS:
        {
            if(transitory)
            {
                if(!lockTransitory)
                {
                    transitory = false;
                }

                if(!transitoryStereoRight.empty())
                {
                    stereoLeftWidget->setImage(transitoryStereoLeft);
                    stereoRightWidget->setImage(transitoryStereoRight);
                }
                else
                {
                    stereoLeftWidget->setImage(transitoryStereoLeft);
                }

                break;
            }

            if(!stereoImages.size())
            {
                return;
            }

            std::vector<StereoImagesState*>::reverse_iterator it = stereoImages.rbegin();
            StereoImagesState* state = *it;

            if(!state->second.empty())
            {
                stereoLeftWidget->setImage(state->first);
                stereoRightWidget->setImage(state->second);
            }
            else
            {
                stereoLeftWidget->setImage(state->first);
            }

            delete *it;
            stereoImages.pop_back();

            break;
        }

        default:
        {
            break;
        }
    }
}

void ApplicationStates::lockTransitoryState(bool value)
{
    lockTransitory = value;
}

void ApplicationStates::destroyStereoStates()
{
    if(!stereoImages.empty())
    {
        for(std::vector<StereoImagesState*>::iterator it = stereoImages.begin(); it != stereoImages.end(); ++it)
        {
            delete *it;
        }
    }
}
