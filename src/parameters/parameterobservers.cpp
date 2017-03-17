#include "parameters/parameterobservers.hpp"

#include "parameters/blurparameters.hpp"
#include "parameters/sobelparameters.hpp"
#include "parameters/cannyparameters.hpp"
#include "parameters/disparitymapparameters.hpp"

#include <iostream>

ParameterObservers::ParameterObservers()
{
    observers = std::vector<Parameters*>(6, nullptr);
}

ParameterObservers::ParameterObservers(std::initializer_list<Observer> init) : ParameterObservers()
{
    for(std::initializer_list<Observer>::iterator it = init.begin(); it != init.end(); ++it)
    {
        switch(*it)
        {
            case ParameterObservers::Observer::OBS_BLUR:
            {
                observers[ParameterObservers::Observer::OBS_BLUR] = new BlurParameters();
                break;
            }

            case ParameterObservers::Observer::OBS_SOBEL:
            {
                observers[ParameterObservers::Observer::OBS_SOBEL] = new SobelParameters();
                break;
            }

            case ParameterObservers::Observer::OBS_CANNY:
            {
                observers[ParameterObservers::Observer::OBS_CANNY] = new CannyParameters();
                break;
            }

            case ParameterObservers::Observer::OBS_DISPARITY:
            {
                observers[ParameterObservers::Observer::OBS_DISPARITY] = new DisparityMapParameters();
                break;
            }
        }
    }
}


ParameterObservers::~ParameterObservers()
{
    for(Parameters* p : observers)
    {
        if(p)
        {
            delete p;
        }
    }
}

void ParameterObservers::addObserver(Observer init)
{
    switch(init)
    {
        case ParameterObservers::Observer::OBS_BLUR:
        {
            if(!observers[ParameterObservers::Observer::OBS_BLUR])
            {
                observers[ParameterObservers::Observer::OBS_BLUR] = new BlurParameters();
            }

            break;
        }

        case ParameterObservers::Observer::OBS_SOBEL:
        {
            if(!observers[ParameterObservers::Observer::OBS_SOBEL])
            {
                observers[ParameterObservers::Observer::OBS_SOBEL] = new SobelParameters();
            }

            break;
        }

        case ParameterObservers::Observer::OBS_CANNY:
        {
            if(!observers[ParameterObservers::Observer::OBS_CANNY])
            {
                observers[ParameterObservers::Observer::OBS_CANNY] = new CannyParameters();
            }

            break;
        }

        case ParameterObservers::Observer::OBS_DISPARITY:
        {
            if(!observers[ParameterObservers::Observer::OBS_DISPARITY])
            {
                observers[ParameterObservers::Observer::OBS_DISPARITY] = new DisparityMapParameters();
            }

            break;
        }
    }
}

Parameters* ParameterObservers::getObserver(Observer which) const
{
    return observers[which];
}
