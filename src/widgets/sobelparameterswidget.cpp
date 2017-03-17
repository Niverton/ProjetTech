#include "widgets/sobelparameterswidget.hpp"

#include "parameters/sobelparameters.hpp"
#include "utils/signalblocker.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>

SobelParametersWidget::SobelParametersWidget(QWidget* parent, Parameters* model) : ParametersWidget("Sobel", parent, model)
{
    QGridLayout* gridLayout =  static_cast<QGridLayout*>(layout());

    dxSpinBox = new QSpinBox(this);
    dxSpinBox->setRange(0, 100);

    dySpinBox = new QSpinBox(this);
    dySpinBox->setRange(0, 100);

    kSizeComboBox = new QComboBox(this);
    kSizeComboBox->addItems(QStringList({"1", "3", "5", "7"}));

    sclSpinBox = new QDoubleSpinBox(this);
    sclSpinBox->setRange(-99.0, 99.0);
    sclSpinBox->setSingleStep(0.1);

    dSpinBox = new QDoubleSpinBox(this);
    dSpinBox->setRange(-99.0, 99.0);
    dSpinBox->setSingleStep(0.1);

    if(model)
    {
        SobelParameters* sp = static_cast<SobelParameters*>(model);
        dxSpinBox->setValue(sp->getDx());
        dySpinBox->setValue(sp->getDy());
        kSizeComboBox->setCurrentIndex(kSizeComboBox->findText(QString::number(sp->getKSize())));
        sclSpinBox->setValue(sp->getScale());
        dSpinBox->setValue(sp->getDelta());
    }
    else
    {
        dxSpinBox->setValue(0);
        dySpinBox->setValue(0);
        kSizeComboBox->setCurrentIndex(0);
        sclSpinBox->setValue(1.0);
        dSpinBox->setValue(0.0);
    }

    QLabel* dxLabel = new QLabel("Derivative X:", this);
    QLabel* dyLabel = new QLabel("Derivative Y:", this);
    QLabel* kSizeLabel = new QLabel("Kernel Size:", this);
    QLabel* sclLabel = new QLabel("Scale factor:", this);
    QLabel* dLabel = new QLabel("Delta:", this);

    gridLayout->addWidget(dxLabel, 2, 0, Qt::AlignLeft);
    gridLayout->addWidget(dyLabel, 3, 0, Qt::AlignLeft);
    gridLayout->addWidget(kSizeLabel, 4, 0, Qt::AlignLeft);
    gridLayout->addWidget(sclLabel, 5, 0, Qt::AlignLeft);
    gridLayout->addWidget(dLabel, 6, 0, Qt::AlignLeft);

    gridLayout->addWidget(dxSpinBox, 2, 1, Qt::AlignLeft);
    gridLayout->addWidget(dySpinBox, 3, 1, Qt::AlignLeft);
    gridLayout->addWidget(kSizeComboBox, 4, 1, Qt::AlignLeft);
    gridLayout->addWidget(sclSpinBox, 5, 1, Qt::AlignLeft);
    gridLayout->addWidget(dSpinBox, 6, 1, Qt::AlignLeft);

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(spacer, 7, 0);

    connect(dxSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setDx(int)));
    connect(dySpinBox, SIGNAL(valueChanged(int)), this, SLOT(setDy(int)));
    connect(kSizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setKSize(int)));
    connect(sclSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setScale(double)));
    connect(dSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setDelta(double)));
}

SobelParametersWidget::~SobelParametersWidget() {}

int SobelParametersWidget::getDx() const
{
    return dxSpinBox->value();
}

int SobelParametersWidget::getDy() const
{
    return dySpinBox->value();
}

int SobelParametersWidget::getKSize() const
{
    switch(kSizeComboBox->currentIndex())
    {
        case 0:
        {
            return 1;
            break;
        }

        case 1:
        {
            return 3;
            break;
        }

        case 2:
        {
            return 5;
            break;
        }

        case 3:
        {
            return 7;
            break;
        }
    }

    return -1;
}

double SobelParametersWidget::getScale() const
{
    return sclSpinBox->value();
}

double SobelParametersWidget::getDelta() const
{
    return dSpinBox->value();
}

void SobelParametersWidget::notify()
{
    if(model())
    {
        model()->update();
        emit valuesChanged();
    }
}

void SobelParametersWidget::update()
{
    if(model())
    {
        SobelParameters* sp = static_cast<SobelParameters*>(model());
        bool realTime = sp->getRealTime();
        int dx = sp->getDx();
        int dy = sp->getDy();
        int kSize = sp->getKSize();
        double scale = sp->getScale();
        double delta = sp->getDelta();

        SignalBlocker sBlocker;

        if(getRealTimeCheckBox()->isChecked() != realTime)
        {
            sBlocker.setObject(getRealTimeCheckBox());
            sBlocker.block();
            getRealTimeCheckBox()->setEnabled(realTime);
            sBlocker.unblock();
        }

        if(dxSpinBox->value() != dx)
        {
            sBlocker.setObject(dxSpinBox);
            sBlocker.block();
            dxSpinBox->setValue(dx);
            sBlocker.unblock();
        }

        if(dySpinBox->value() != dy)
        {
            sBlocker.setObject(dySpinBox);
            sBlocker.block();
            dySpinBox->setValue(dy);
            sBlocker.unblock();
        }

        if(getKSize() != kSize)
        {
            sBlocker.setObject(kSizeComboBox);
            sBlocker.block();
            kSizeComboBox->setCurrentIndex(kSizeComboBox->findText(QString::number(kSize)));
            sBlocker.unblock();
        }

        if(sclSpinBox->value() != scale)
        {
            sBlocker.setObject(sclSpinBox);
            sBlocker.block();
            sclSpinBox->setValue(scale);
            sBlocker.unblock();
        }

        if(dSpinBox->value() != delta)
        {
            sBlocker.setObject(dSpinBox);
            sBlocker.block();
            dSpinBox->setValue(delta);
            sBlocker.unblock();
        }

        if(sBlocker.hasObject())
        {
            emit valuesChanged();
        }
    }
}

void SobelParametersWidget::setDx(int)
{
    notify();
}

void SobelParametersWidget::setDy(int)
{
    notify();
}

void SobelParametersWidget::setKSize(int)
{
    notify();
}

void SobelParametersWidget::setScale(double)
{
    notify();
}

void SobelParametersWidget::setDelta(double)
{
    notify();
}
