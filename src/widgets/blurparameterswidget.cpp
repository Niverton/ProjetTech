#include "widgets/blurparameterswidget.hpp"

#include "parameters/blurparameters.hpp"
#include "utils/signalblocker.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>

BlurParametersWidget::BlurParametersWidget(QWidget* parent, Parameters* model) : ParametersWidget("Blur", parent, model)
{
    QGridLayout* gridLayout = static_cast<QGridLayout*>(layout());

    kWSpinBox = new QSpinBox(this);
    kWSpinBox->setMinimum(1);

    kHSpinBox = new QSpinBox(this);
    kHSpinBox->setMinimum(1);

    if(model)
    {
        BlurParameters* bp = static_cast<BlurParameters*>(model);
        kWSpinBox->setValue(bp->getKSizeW());
        kHSpinBox->setValue(bp->getKSizeH());
    }
    else
    {
        kWSpinBox->setValue(1);
        kHSpinBox->setValue(1);
    }

    QLabel* labelKW = new QLabel("Kernel Width:", this);
    QLabel* labelkH = new QLabel("Kernel Height", this);

    gridLayout->addWidget(labelKW, 2, 0, Qt::AlignLeft);
    gridLayout->addWidget(labelkH, 3, 0, Qt::AlignLeft);

    gridLayout->addWidget(kWSpinBox, 2, 1, Qt::AlignLeft);
    gridLayout->addWidget(kHSpinBox, 3, 1, Qt::AlignLeft);

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(spacer, 4, 0);

    connect(kWSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setKSizeW(int)));
    connect(kHSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setKSizeH(int)));
}

BlurParametersWidget::~BlurParametersWidget() {}

int BlurParametersWidget::getKSizeW() const
{
    return kWSpinBox->value();
}

int BlurParametersWidget::getKSizeH() const
{
    return kHSpinBox->value();
}

void BlurParametersWidget::notify()
{
    if(model())
    {
        model()->update();
        emit valuesChanged();
    }
}

void BlurParametersWidget::update()
{
    if(model())
    {
        BlurParameters* bp = static_cast<BlurParameters*>(model());
        bool realTime = bp->getRealTime();
        int kSizeW = bp->getKSizeW();
        int kSizeH = bp->getKSizeH();

        SignalBlocker sBlocker;

        if(getRealTimeCheckBox()->isChecked() != realTime)
        {
            sBlocker.setObject(getRealTimeCheckBox());
            sBlocker.block();
            getRealTimeCheckBox()->setEnabled(realTime);
            sBlocker.unblock();
        }

        if(kWSpinBox->value() != kSizeW)
        {
            sBlocker.setObject(kWSpinBox);
            sBlocker.block();
            kWSpinBox->setValue(kSizeW);
            sBlocker.unblock();
        }

        if(kHSpinBox->value() != kSizeH)
        {
            sBlocker.setObject(kHSpinBox);
            sBlocker.block();
            kHSpinBox->setValue(kSizeH);
            sBlocker.unblock();
        }

        if(sBlocker.hasObject())
        {
            emit valuesChanged();
        }
    }
}

void BlurParametersWidget::setKSizeW(int)
{
    notify();
}
void BlurParametersWidget::setKSizeH(int)
{
    notify();
}

void BlurParametersWidget::setKSize(int kW, int kH)
{
    setKSizeW(kW);
    setKSizeH(kH);
}
