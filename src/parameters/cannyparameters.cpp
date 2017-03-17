#include "parameters/cannyparameters.hpp"

#include "widgets/cannyparameterswidget.hpp"

CannyParameters::CannyParameters() : Parameters(), hThrA(20.0), hThrB(40.0), aperture(3), gMagnitude(false) {}

CannyParameters::CannyParameters(QWidget* view) : Parameters(view), hThrA(20.0), hThrB(40.0), aperture(3), gMagnitude(false) {}

CannyParameters::~CannyParameters() {}

void CannyParameters::setHThrA(double thr)
{
    hThrA = thr;
    notify();
}

void CannyParameters::setHThrB(double thr)
{
    hThrB = thr;
    notify();
}

void CannyParameters::setAperture(int ap)
{
    aperture = ap;
    notify();
}

void CannyParameters::setGMagnitude(bool value)
{
    gMagnitude = value;
}

double CannyParameters::getHThrA() const
{
    return hThrA;
}

double CannyParameters::getHThrB() const
{
    return hThrB;
}

int CannyParameters::getAperture() const
{
    return aperture;
}

bool CannyParameters::getGMagnitude() const
{
    return gMagnitude;
}

void CannyParameters::update()
{
    if(view())
    {
        CannyParametersWidget* cpw = static_cast<CannyParametersWidget*>(view());
        setRealTime(cpw->hasRealTime());
        hThrA = cpw->getHThrA();
        hThrB = cpw->getHThrB();
        aperture = cpw->getAperture();
        gMagnitude = cpw->getGMagnitude();
    }
}

void CannyParameters::notify()
{
    if(view())
    {
        view()->update();
    }
}
