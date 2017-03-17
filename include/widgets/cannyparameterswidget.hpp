#ifndef CANNYPARAMETERSWIDGET_HPP
#define CANNYPARAMETERSWIDGET_HPP

#include "widgets/parameterswidget.hpp"

class QDoubleSpinBox;
class QComboBox;
class QCheckBox;
class QPushButton;

class CannyParametersWidget : public ParametersWidget
{
    Q_OBJECT

public:
    CannyParametersWidget(QWidget* parent = nullptr, Parameters* model = nullptr);
    ~CannyParametersWidget();

    double getHThrA() const;
    double getHThrB() const;
    int getAperture() const;
    bool getGMagnitude() const;

    void notify();
    void update();

private slots:
    void setHThrA(double);
    void setHThrB(double);
    void setAperture(int);
    void setGMagnitude(int);

private:
    QDoubleSpinBox* thrASpinBox;
    QDoubleSpinBox* thrBSpinBox;

    QComboBox* apComboBox;

    QCheckBox* magnCheckBox;
};

#endif // CANNYPARAMETERSWIDGET_HPP
