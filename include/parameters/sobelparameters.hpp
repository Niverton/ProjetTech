#ifndef SOBELPARAMETERS_HPP
#define SOBELPARAMETERS_HPP

#include "parameters/parameters.hpp"

class SobelParameters : public Parameters
{
public:
    SobelParameters();
    SobelParameters(QWidget* view);
    ~SobelParameters();

    void setDx(int derX);
    void setDy(int derY);
    void setKSize(int kSz);
    void setScale(double scl);
    void setDelta(double d);

    int getDx() const;
    int getDy() const;
    int getKSize() const;
    double getScale() const;
    double getDelta() const;

    void update();
    void notify();

private:
    int dx;
    int dy;
    int kSize;

    double scale;
    double delta;
};

#endif // SOBELPARAMETERS_HPP
