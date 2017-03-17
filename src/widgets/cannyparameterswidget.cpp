#include "widgets/cannyparameterswidget.hpp"

#include "parameters/cannyparameters.hpp"
#include "utils/signalblocker.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFile>

CannyParametersWidget::CannyParametersWidget(QWidget* parent, Parameters* model) : ParametersWidget("Canny", parent, model)
{
    QGridLayout* gridLayout = static_cast<QGridLayout*>(layout());

    thrASpinBox = new QDoubleSpinBox(this);
    thrASpinBox->setRange(0.0, 100.0);
    thrASpinBox->setSingleStep(0.2);

    thrBSpinBox = new QDoubleSpinBox(this);
    thrBSpinBox->setRange(0.0, 500.0);
    thrBSpinBox->setSingleStep(0.2);

    apComboBox = new QComboBox(this);
    apComboBox->addItems(QStringList({"3", "5", "7"}));

    magnCheckBox = new QCheckBox("Accurate gradient magnitude", this);

    if(model)
    {
        CannyParameters* cp = static_cast<CannyParameters*>(model);
        thrASpinBox->setValue(cp->getHThrA());
        thrBSpinBox->setValue(cp->getHThrB());
        apComboBox->setCurrentIndex(apComboBox->findText(QString::number(cp->getAperture())));
        magnCheckBox->setChecked(cp->getGMagnitude());
    }
    else
    {
        thrASpinBox->setValue(10.0);
        thrBSpinBox->setValue(20.0);
        apComboBox->setCurrentIndex(0);
        magnCheckBox->setChecked(false);
    }

    QLabel* thrALabel = new QLabel("Hysteresis Threshold 1:", this);
    QLabel* thrBLabel = new QLabel("Hysteresis Threshold 2:", this);
    QLabel* apLabel = new QLabel("Aperture Size:", this);

    gridLayout->addWidget(thrALabel, 2, 0, Qt::AlignLeft);
    gridLayout->addWidget(thrBLabel, 3, 0, Qt::AlignLeft);
    gridLayout->addWidget(apLabel, 4, 0, Qt::AlignLeft);

    gridLayout->addWidget(thrASpinBox, 2, 1, Qt::AlignLeft);
    gridLayout->addWidget(thrBSpinBox, 3, 1, Qt::AlignLeft);
    gridLayout->addWidget(apComboBox, 4, 1, Qt::AlignLeft);
    gridLayout->addWidget(magnCheckBox, 5, 0, Qt::AlignLeft);

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(spacer, 6, 0);

    connect(thrASpinBox, SIGNAL(valueChanged(double)), this, SLOT(setHThrA(double)));
    connect(thrBSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setHThrB(double)));
    connect(apComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setAperture(int)));
    connect(magnCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setGMagnitude(int)));
}

CannyParametersWidget::~CannyParametersWidget() {}

double CannyParametersWidget::getHThrA() const
{
    return thrASpinBox->value();
}

double CannyParametersWidget::getHThrB() const
{
    return thrBSpinBox->value();
}

int CannyParametersWidget::getAperture() const
{
    switch(apComboBox->currentIndex())
    {
        case 0:
        {
            return 3;
            break;
        }

        case 1:
        {
            return 5;
            break;
        }

        case 2:
        {
            return 7;
            break;
        }
    }

    return -1;
}

bool CannyParametersWidget::getGMagnitude() const
{
    return magnCheckBox->isChecked();
}

void CannyParametersWidget::notify()
{
    if(model())
    {
        model()->update();
        emit valuesChanged();
    }
}

void CannyParametersWidget::update()
{
    if(model())
    {
        CannyParameters* cp = static_cast<CannyParameters*>(model());
        bool realTime = cp->getRealTime();
        double hThrA = cp->getHThrA();
        double hThrB = cp->getHThrB();
        int aperture = cp->getAperture();
        bool gMagnitude = cp->getGMagnitude();

        SignalBlocker sBlocker;

        if(getRealTimeCheckBox()->isChecked() != realTime)
        {
            sBlocker.setObject(getRealTimeCheckBox());
            sBlocker.block();
            getRealTimeCheckBox()->setEnabled(realTime);
            sBlocker.unblock();
        }

        if(thrASpinBox->value() != hThrA)
        {
            sBlocker.setObject(thrASpinBox);
            sBlocker.block();
            thrASpinBox->setValue(hThrA);
            sBlocker.unblock();
        }

        if(thrBSpinBox->value() != hThrB)
        {
            sBlocker.setObject(thrBSpinBox);
            sBlocker.block();
            thrBSpinBox->setValue(hThrB);
            sBlocker.unblock();
        }

        if(getAperture() != aperture)
        {
            sBlocker.setObject(apComboBox);
            sBlocker.block();
            apComboBox->setCurrentIndex(apComboBox->findText(QString::number(aperture)));
            sBlocker.unblock();
        }

        if(magnCheckBox->isChecked() != gMagnitude)
        {
            sBlocker.setObject(magnCheckBox);
            sBlocker.block();
            magnCheckBox->setChecked(gMagnitude);
            sBlocker.unblock();
        }

        if(sBlocker.hasObject())
        {
            emit valuesChanged();
        }
    }
}

void CannyParametersWidget::setHThrA(double)
{
    notify();
}

void CannyParametersWidget::setHThrB(double)
{
    notify();
}

void CannyParametersWidget::setAperture(int)
{
    notify();
}

void CannyParametersWidget::setGMagnitude(int)
{
    notify();
}
