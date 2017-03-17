#ifndef CANNYPARAMETERS_HPP
#define CANNYPARAMETERS_HPP

#include "parameters/parameters.hpp"

class CannyParameters : public Parameters
{
public:
    CannyParameters();
    CannyParameters(QWidget* view);
    ~CannyParameters();

    void setHThrA(double thr);
    void setHThrB(double thr);
    void setAperture(int ap);
    void setGMagnitude(bool value);

    double getHThrA() const;
    double getHThrB() const;
    int getAperture() const;
    bool getGMagnitude() const;

    void update();
    void notify();

private:
    double hThrA;
    double hThrB;

    int aperture;

    bool gMagnitude;
};

#endif // CANNYPARAMETERS_HPP
