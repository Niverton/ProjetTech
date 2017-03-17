#include "parameters/sobelparameters.hpp"

#include "widgets/sobelparameterswidget.hpp"

SobelParameters::SobelParameters() : Parameters(), dx(1), dy(0), kSize(3), scale(1), delta(0) {}

SobelParameters::SobelParameters(QWidget* view) : Parameters(view), dx(1), dy(0), kSize(3), scale(1), delta(0) {}

SobelParameters::~SobelParameters() {}

void SobelParameters::setDx(int derX)
{
    dx = derX;
    notify();
}

void SobelParameters::setDy(int derY)
{
    dy = derY;
    notify();
}

void SobelParameters::setKSize(int kSz)
{
    kSize = kSz;
    notify();
}

void SobelParameters::setScale(double scl)
{
    scale = scl;
    notify();
}

void SobelParameters::setDelta(double d)
{
    delta = d;
    notify();
}

int SobelParameters::getDx() const
{
    return dx;
}

int SobelParameters::getDy() const
{
    return dy;
}

int SobelParameters::getKSize() const
{
    return kSize;
}

double SobelParameters::getScale() const
{
    return scale;
}

double SobelParameters::getDelta() const
{
    return delta;
}

void SobelParameters::update()
{
    if(view())
    {
        SobelParametersWidget* spw = static_cast<SobelParametersWidget*>(view());
        setRealTime(spw->hasRealTime());
        dx = spw->getDx();
        dy = spw->getDy();
        kSize = spw->getKSize();
        scale = spw->getScale();
        delta = spw->getDelta();
    }
}

void SobelParameters::notify()
{
    if(view())
    {
        view()->update();
    }
}
