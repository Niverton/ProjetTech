#ifndef PARAMETEROBSERVERS_HPP
#define PARAMETEROBSERVERS_HPP

#include <initializer_list>
#include <vector>

class Parameters;

class ParameterObservers
{
public:
    enum Observer
    {
        OBS_BLUR = 0,
        OBS_SOBEL,
        OBS_CANNY,
        OBS_DISPARITY
    };

public:
    ParameterObservers();
    ParameterObservers(std::initializer_list<Observer> init);
    ~ParameterObservers();

    void addObserver(Observer init);

    Parameters* getObserver(Observer which) const;

private:
    std::vector<Parameters*> observers;
};

#endif // PARAMETEROBSERVERS_H
