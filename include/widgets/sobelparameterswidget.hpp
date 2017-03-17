#ifndef SOBELPARAMETERSWIDGET_H
#define SOBELPARAMETERSWIDGET_H

#include "widgets/parameterswidget.hpp"

class QSpinBox;
class QPushButton;
class QComboBox;
class QDoubleSpinBox;

class SobelParametersWidget : public ParametersWidget
{
    Q_OBJECT

public:
    SobelParametersWidget(QWidget* parent = nullptr, Parameters* model = nullptr);
    ~SobelParametersWidget();

    int getDx() const;
    int getDy() const;
    int getKSize() const;
    double getScale() const;
    double getDelta() const;

    void notify();
    void update();

private slots:
    void setDx(int derX);
    void setDy(int derY);
    void setKSize(int kSz);
    void setScale(double scl);
    void setDelta(double d);

private:
    QSpinBox* dxSpinBox;
    QSpinBox* dySpinBox;

    QComboBox* kSizeComboBox;

    QDoubleSpinBox* sclSpinBox;
    QDoubleSpinBox* dSpinBox;
};

#endif // SOBELPARAMETERSWIDGET_HPP
