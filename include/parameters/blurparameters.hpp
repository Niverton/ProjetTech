#ifndef BLURPARAMETERS_HPP
#define BLURPARAMETERS_HPP

#include "parameters/parameters.hpp"

class BlurParameters : public Parameters
{
public:
    BlurParameters();
    BlurParameters(QWidget* view);
    ~BlurParameters();

    void setKSize(int kW, int kH);
    void setKSizeW(int kW);
    void setKSizeH(int kH);

    int getKSizeW() const;
    int getKSizeH() const;

    void update();
    void notify();

private:
    int kSizeW;
    int kSizeH;
};

#endif // BLURPARAMETERS_HPP
