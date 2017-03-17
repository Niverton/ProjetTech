#include "parameters/blurparameters.hpp"

#include "widgets/blurparameterswidget.hpp"


BlurParameters::BlurParameters() : Parameters(), kSizeW(3), kSizeH(3) {}

BlurParameters::BlurParameters(QWidget* view) : Parameters(view), kSizeW(3), kSizeH(3) {}

BlurParameters::~BlurParameters() {}

void BlurParameters::setKSize(int kW, int kH)
{
    kSizeW = kW;
    kSizeH = kH;
}

void BlurParameters::setKSizeW(int kW)
{
    kSizeW = kW;
    notify();

}
void BlurParameters::setKSizeH(int kH)
{
    kSizeH = kH;
    notify();
}

int BlurParameters::getKSizeW() const
{
    return kSizeW;
}

int BlurParameters::getKSizeH() const
{
    return kSizeH;
}

void BlurParameters::update()
{
    if(view())
    {
        BlurParametersWidget* bpw = static_cast<BlurParametersWidget*>(view());
        setRealTime(bpw->hasRealTime());
        setKSize(bpw->getKSizeW(), bpw->getKSizeH());
    }
}

void BlurParameters::notify()
{
    if(view())
    {
        view()->update();
    }
}
