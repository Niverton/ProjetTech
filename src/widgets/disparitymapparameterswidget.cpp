#include "widgets/disparitymapparameterswidget.hpp"

#include "parameters/disparitymapparameters.hpp"
#include "utils/signalblocker.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QPushButton>

DisparityMapParametersWidget::DisparityMapParametersWidget(QWidget* parent, Parameters* model) : ParametersWidget("Disparity map", parent, model)
{
    getRealTimeCheckBox()->setEnabled(false);

    QGridLayout* gridLayout = static_cast<QGridLayout*>(layout());

    algorithmComboBox = new QComboBox(this);
    algorithmComboBox->addItem("StereoBM");
    algorithmComboBox->addItem("StereoSGBM");
    algorithmComboBox->addItem("StereoBM GPU");
    algorithmComboBox->setCurrentIndex(0);

    preFilterTypeComboBox = new QComboBox(this);
    preFilterTypeComboBox->addItem("PREFILTER_NORMALIZED_RESPONSE");
    preFilterTypeComboBox->addItem("PREFILTER_XSOBEL");
    preFilterTypeComboBox->addItem("NARROW_PRESET");

    preFilterSizeSlider = new QSlider(Qt::Horizontal, this);
    preFilterSizeSlider->setMinimum(0);
    preFilterSizeSlider->setMaximum(256);
    preFilterSizeSlider->setSingleStep(1);
    preFilterSizeSlider->setPageStep(1);
    preFilterSizeSlider->setTickInterval(1);

    preFilterCapSlider = new QSlider(Qt::Horizontal, this);
    preFilterCapSlider->setMinimum(0);
    preFilterCapSlider->setMaximum(256);
    preFilterCapSlider->setSingleStep(1);
    preFilterCapSlider->setPageStep(1);
    preFilterCapSlider->setTickInterval(1);

    SADWindowSizeSlider = new QSlider(Qt::Horizontal, this);
    SADWindowSizeSlider->setMinimum(0);
    SADWindowSizeSlider->setMaximum(64);
    SADWindowSizeSlider->setSingleStep(1);
    SADWindowSizeSlider->setPageStep(1);
    SADWindowSizeSlider->setTickInterval(1);

    minDisparitySlider = new QSlider(Qt::Horizontal, this);
    minDisparitySlider->setMinimum(-256);
    minDisparitySlider->setMaximum(256);
    minDisparitySlider->setSingleStep(1);
    minDisparitySlider->setPageStep(1);
    minDisparitySlider->setTickInterval(1);

    numberOfDisparitiesSlider = new QSlider(Qt::Horizontal, this);
    numberOfDisparitiesSlider->setMinimum(16);
    numberOfDisparitiesSlider->setMaximum(1024);
    numberOfDisparitiesSlider->setSingleStep(16);
    numberOfDisparitiesSlider->setPageStep(16);
    numberOfDisparitiesSlider->setTickInterval(16);

    textureThresholdSlider = new QSlider(Qt::Horizontal, this);
    textureThresholdSlider->setMinimum(0);
    textureThresholdSlider->setMaximum(256);
    textureThresholdSlider->setSingleStep(1);
    textureThresholdSlider->setPageStep(1);
    textureThresholdSlider->setTickInterval(1);

    uniquenessRatioSlider = new QSlider(Qt::Horizontal, this);
    uniquenessRatioSlider->setMinimum(0);
    uniquenessRatioSlider->setMaximum(256);
    uniquenessRatioSlider->setSingleStep(1);
    uniquenessRatioSlider->setPageStep(1);
    uniquenessRatioSlider->setTickInterval(1);

    speckleWindowSizeSlider = new QSlider(Qt::Horizontal, this);
    speckleWindowSizeSlider->setMinimum(0);
    speckleWindowSizeSlider->setMaximum(256);
    speckleWindowSizeSlider->setSingleStep(1);
    speckleWindowSizeSlider->setPageStep(1);
    speckleWindowSizeSlider->setTickInterval(1);

    speckleRangeSlider = new QSlider(Qt::Horizontal, this);
    speckleRangeSlider->setMinimum(0);
    speckleRangeSlider->setMaximum(10);
    speckleRangeSlider->setSingleStep(1);
    speckleRangeSlider->setPageStep(1);
    speckleRangeSlider->setTickInterval(1);

    disp12MaxDiffSlider = new QSlider(Qt::Horizontal, this);
    disp12MaxDiffSlider->setMinimum(-1);
    disp12MaxDiffSlider->setMaximum(256);
    disp12MaxDiffSlider->setSingleStep(1);
    disp12MaxDiffSlider->setPageStep(1);
    disp12MaxDiffSlider->setTickInterval(1);

    averageTextureThresholdSpinBox = new QDoubleSpinBox(this);
    averageTextureThresholdSpinBox->setMinimum(0.0);
    averageTextureThresholdSpinBox->setMaximum(10.0);
    averageTextureThresholdSpinBox->setSingleStep(0.2);

    averageTextureThresholdSpinBox->setValue(0.0);

    fullDPCheckBox = new QCheckBox("Full-scale two-pass dynamic.", this);

    if(model)
    {
        DisparityMapParameters* dmp = static_cast<DisparityMapParameters*>(model);
        preFilterTypeComboBox->setCurrentIndex(dmp->getPreFilterType());
        preFilterSizeSlider->setValue(dmp->getPrefilterSize());
        preFilterCapSlider->setValue(dmp->getPreFilterCap());
        SADWindowSizeSlider->setValue(dmp->getSADWindowSize());
        minDisparitySlider->setValue(dmp->getMinDisparity());
        numberOfDisparitiesSlider->setValue(dmp->getNumberOfDisparities());
        textureThresholdSlider->setValue(dmp->getTextureThreshold());
        uniquenessRatioSlider->setValue(dmp->getUniquenessRatio());
        speckleWindowSizeSlider->setValue(dmp->getSpeckleWindowSize());
        speckleRangeSlider->setValue(dmp->getSpeckleRange());
        disp12MaxDiffSlider->setValue(dmp->getDisp12MaxDiff());
        averageTextureThresholdSpinBox->setValue(dmp->getAverageTextureThreshold());
        fullDPCheckBox->setChecked(dmp->getFullDP());
    }
    else
    {
        preFilterTypeComboBox->setCurrentIndex(0);
        preFilterSizeSlider->setValue(1);
        preFilterCapSlider->setValue(1);
        SADWindowSizeSlider->setValue(0);
        minDisparitySlider->setValue(0);
        numberOfDisparitiesSlider->setValue(16);
        textureThresholdSlider->setValue(0);
        uniquenessRatioSlider->setValue(0);
        speckleWindowSizeSlider->setValue(0);
        speckleRangeSlider->setValue(0);
        disp12MaxDiffSlider->setValue(-1);
        averageTextureThresholdSpinBox->setValue(0.0);
        fullDPCheckBox->setChecked(false);
    }

    algorithmLabel = new QLabel("Algorithm:", this);
    preFilterTypeLabel = new QLabel("Pre-filter:", this);
    preFilterSizeLabel = new QLabel("Pre-filter size:", this);
    preFilterCapLabel = new QLabel("Pre-filter clip:", this);
    SADWindowSizeLabel = new QLabel("SAD Window:", this);
    minDisparityLabel = new QLabel("Minimum disparity:", this);
    numberOfDisparitiesLabel = new QLabel("Number of disparities:", this);
    textureThresholdLabel = new QLabel("Texture threshold", this);
    uniquenessRatioLabel = new QLabel("Uniqueness ratio:", this);
    speckleWindowSizeLabel = new QLabel("Speckle size:", this);
    speckleRangeLabel = new QLabel("Speckle range:", this);
    disp12MaxDiffLabel = new QLabel("Disparity max. difference:", this);
    averageTextureThresholdLabel = new QLabel("Average tex. threshold:", this);

    preFilterSizeValueLabel = new QLabel(QString::number(preFilterSizeSlider->value()), this);
    preFilterCapValueLabel = new QLabel(QString::number(preFilterCapSlider->value()), this);
    SADWindowSizeValueLabel = new QLabel(QString::number(SADWindowSizeSlider->value()), this);
    minDisparityValueLabel = new QLabel(QString::number(minDisparitySlider->value()), this);
    numberOfDisparitiesValueLabel = new QLabel(QString::number(numberOfDisparitiesSlider->value()), this);
    textureThresholdValueLabel = new QLabel(QString::number(textureThresholdSlider->value()), this);
    uniquenessRatioValueLabel = new QLabel(QString::number(uniquenessRatioSlider->value()), this);
    speckleWindowSizeValueLabel = new QLabel(QString::number(speckleWindowSizeSlider->value()), this);
    speckleRangeValueLabel = new QLabel(QString::number(speckleRangeSlider->value()), this);
    disp12MaxDiffValueLabel = new QLabel(QString::number(disp12MaxDiffSlider->value()), this);

    gridLayout->addWidget(algorithmLabel, 2, 0, Qt::AlignLeft);
    gridLayout->addWidget(preFilterTypeLabel, 3, 0, Qt::AlignLeft);
    gridLayout->addWidget(preFilterSizeLabel, 4, 0, Qt::AlignLeft);
    gridLayout->addWidget(preFilterCapLabel, 5, 0, Qt::AlignLeft);
    gridLayout->addWidget(SADWindowSizeLabel, 6, 0, Qt::AlignLeft);
    gridLayout->addWidget(minDisparityLabel, 7, 0, Qt::AlignLeft);
    gridLayout->addWidget(numberOfDisparitiesLabel, 8, 0, Qt::AlignLeft);
    gridLayout->addWidget(textureThresholdLabel, 9, 0, Qt::AlignLeft);
    gridLayout->addWidget(uniquenessRatioLabel, 10, 0, Qt::AlignLeft);
    gridLayout->addWidget(speckleWindowSizeLabel, 11, 0, Qt::AlignLeft);
    gridLayout->addWidget(speckleRangeLabel, 12, 0, Qt::AlignLeft);
    gridLayout->addWidget(disp12MaxDiffLabel, 13, 0, Qt::AlignLeft);
    gridLayout->addWidget(averageTextureThresholdLabel, 14, 0, Qt::AlignLeft);
    gridLayout->addWidget(fullDPCheckBox, 15, 0, Qt::AlignLeft);

    gridLayout->addWidget(algorithmComboBox, 2, 1, Qt::AlignRight);
    gridLayout->addWidget(preFilterTypeComboBox, 3, 1, Qt::AlignRight);
    gridLayout->addWidget(preFilterSizeSlider, 4, 1);
    gridLayout->addWidget(preFilterCapSlider, 5, 1);
    gridLayout->addWidget(SADWindowSizeSlider, 6, 1);
    gridLayout->addWidget(minDisparitySlider, 7, 1);
    gridLayout->addWidget(numberOfDisparitiesSlider, 8, 1);
    gridLayout->addWidget(textureThresholdSlider, 9, 1);
    gridLayout->addWidget(uniquenessRatioSlider, 10, 1);
    gridLayout->addWidget(speckleWindowSizeSlider, 11, 1);
    gridLayout->addWidget(speckleRangeSlider, 12, 1);
    gridLayout->addWidget(disp12MaxDiffSlider, 13, 1);
    gridLayout->addWidget(averageTextureThresholdSpinBox, 14, 1, Qt::AlignRight);

    gridLayout->addWidget(preFilterSizeValueLabel, 4, 2);
    gridLayout->addWidget(preFilterCapValueLabel, 5, 2);
    gridLayout->addWidget(SADWindowSizeValueLabel, 6, 2);
    gridLayout->addWidget(minDisparityValueLabel, 7, 2);
    gridLayout->addWidget(numberOfDisparitiesValueLabel, 8, 2);
    gridLayout->addWidget(textureThresholdValueLabel, 9, 2);
    gridLayout->addWidget(uniquenessRatioValueLabel, 10, 2);
    gridLayout->addWidget(speckleWindowSizeValueLabel, 11, 2);
    gridLayout->addWidget(speckleRangeValueLabel, 12, 2);
    gridLayout->addWidget(disp12MaxDiffValueLabel, 13, 2);

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(spacer, 16, 0);

    connect(getApplyPushButton(), SIGNAL(clicked()), this, SLOT(enableRealtime()));

    connect(preFilterSizeSlider, SIGNAL(valueChanged(int)), preFilterSizeValueLabel, SLOT(setNum(int)));
    connect(preFilterCapSlider, SIGNAL(valueChanged(int)), preFilterCapValueLabel, SLOT(setNum(int)));
    connect(SADWindowSizeSlider, SIGNAL(valueChanged(int)), SADWindowSizeValueLabel, SLOT(setNum(int)));
    connect(minDisparitySlider, SIGNAL(valueChanged(int)), minDisparityValueLabel, SLOT(setNum(int)));
    connect(numberOfDisparitiesSlider, SIGNAL(valueChanged(int)), numberOfDisparitiesValueLabel, SLOT(setNum(int)));
    connect(textureThresholdSlider, SIGNAL(valueChanged(int)), textureThresholdValueLabel, SLOT(setNum(int)));
    connect(uniquenessRatioSlider, SIGNAL(valueChanged(int)), uniquenessRatioValueLabel, SLOT(setNum(int)));
    connect(speckleWindowSizeSlider, SIGNAL(valueChanged(int)), speckleWindowSizeValueLabel, SLOT(setNum(int)));
    connect(speckleRangeSlider, SIGNAL(valueChanged(int)), speckleRangeValueLabel, SLOT(setNum(int)));
    connect(disp12MaxDiffSlider, SIGNAL(valueChanged(int)), disp12MaxDiffValueLabel, SLOT(setNum(int)));

    connect(algorithmComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setAlgorithm(int)));
    connect(preFilterTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setPreFilterType(int)));
    connect(preFilterSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setPrefilterSize(int)));
    connect(preFilterCapSlider, SIGNAL(valueChanged(int)), this, SLOT(setPreFilterCap(int)));
    connect(SADWindowSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setSADWindowSize(int)));
    connect(minDisparitySlider, SIGNAL(valueChanged(int)), this, SLOT(setMinDisparity(int)));
    connect(numberOfDisparitiesSlider, SIGNAL(valueChanged(int)), this, SLOT(setNumberOfDisparities(int)));
    connect(textureThresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(setTextureThreshold(int)));
    connect(uniquenessRatioSlider, SIGNAL(valueChanged(int)), this, SLOT(setUniquenessRatio(int)));
    connect(speckleWindowSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeckleWindowSize(int)));
    connect(speckleRangeSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeckleRange(int)));
    connect(disp12MaxDiffSlider, SIGNAL(valueChanged(int)), this, SLOT(setDisp12MaxDiff(int)));
    connect(averageTextureThresholdSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setAverageTextureThreshold(double)));
    connect(fullDPCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setFullDP(int)));

    averageTextureThresholdLabel->hide();
    averageTextureThresholdSpinBox->hide();
    fullDPCheckBox->hide();

    connect(algorithmComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(enableItems(int)));
}

DisparityMapParametersWidget::~DisparityMapParametersWidget() {}

int DisparityMapParametersWidget::getAlgorithm() const
{
    return algorithmComboBox->currentIndex();
}

int DisparityMapParametersWidget::getPreFilterType() const
{
    return preFilterTypeComboBox->currentIndex();
}

int DisparityMapParametersWidget::getPrefilterSize() const
{
    return preFilterSizeSlider->value();
}

int DisparityMapParametersWidget::getPreFilterCap() const
{
    return preFilterCapSlider->value();
}

int DisparityMapParametersWidget::getSADWindowSize() const
{
    return SADWindowSizeSlider->value();
}

int DisparityMapParametersWidget::getMinDisparity() const
{
    return minDisparitySlider->value();
}

int DisparityMapParametersWidget::getNumberOfDisparities() const
{
    return numberOfDisparitiesSlider->value();
}

int DisparityMapParametersWidget::getTextureThreshold() const
{
    return textureThresholdSlider->value();
}

int DisparityMapParametersWidget::getUniquenessRatio() const
{
    return uniquenessRatioSlider->value();
}

int DisparityMapParametersWidget::getSpeckleWindowSize() const
{
    return speckleWindowSizeSlider->value();
}

int DisparityMapParametersWidget::getSpeckleRange() const
{
    return speckleRangeSlider->value();
}

int DisparityMapParametersWidget::getDisp12MaxDiff() const
{
    return disp12MaxDiffSlider->value();
}

float DisparityMapParametersWidget::getAverageTextureThreshold() const
{
    return static_cast<float>(averageTextureThresholdSpinBox->value());
}

bool DisparityMapParametersWidget::getFullDP() const
{
    return fullDPCheckBox->isChecked();
}

void DisparityMapParametersWidget::notify()
{
    if(model())
    {
        model()->update();
        emit valuesChanged();
    }
}

void DisparityMapParametersWidget::update()
{
    if(model())
    {
        DisparityMapParameters* dmp = static_cast<DisparityMapParameters*>(model());
        bool realTime = dmp->getRealTime();
        int algorithm = dmp->getAlgorithm();
        int prefilterType = dmp->getPreFilterType();
        int preFilterSize = dmp->getPrefilterSize();
        int preFilterCap = dmp->getPreFilterCap();
        int SADWindowSize = dmp->getSADWindowSize();
        int minDisparity = dmp->getMinDisparity();
        int numberOfDisparities = dmp->getNumberOfDisparities();
        int textureThreshold = dmp->getTextureThreshold();
        int uniquenessRatio = dmp->getUniquenessRatio();
        int speckleWindowSize = dmp->getSpeckleWindowSize();
        int speckleRange = dmp->getSpeckleRange();
        int disp12MaxDiff = dmp->getDisp12MaxDiff();
        float averageTextureThreshold = dmp->getAverageTextureThreshold();
        bool fullDP = dmp->getFullDP();

        SignalBlocker sBlocker;

        if(getRealTimeCheckBox()->isChecked() != realTime)
        {
            sBlocker.setObject(getRealTimeCheckBox());
            sBlocker.block();
            getRealTimeCheckBox()->setEnabled(realTime);
            sBlocker.unblock();
        }

        if(algorithmComboBox->currentIndex() != algorithm)
        {
            sBlocker.setObject(algorithmComboBox);
            sBlocker.block();
            algorithmComboBox->setCurrentIndex(algorithm);
            sBlocker.unblock();
        }

        if(preFilterTypeComboBox->currentIndex() != prefilterType)
        {
            sBlocker.setObject(preFilterTypeComboBox);
            sBlocker.block();
            preFilterTypeComboBox->setCurrentIndex(prefilterType);
            sBlocker.unblock();
        }

        if(preFilterSizeSlider->value() != preFilterSize)
        {
            sBlocker.setObject(preFilterSizeSlider);
            sBlocker.block();
            preFilterSizeSlider->setValue(preFilterSize);
            sBlocker.unblock();
        }

        if(preFilterCapSlider->value() != preFilterCap)
        {
            sBlocker.setObject(preFilterCapSlider);
            sBlocker.block();
            preFilterCapSlider->setValue(preFilterCap);
            sBlocker.unblock();
        }

        if(SADWindowSizeSlider->value() != SADWindowSize)
        {
            sBlocker.setObject(SADWindowSizeSlider);
            sBlocker.block();
            SADWindowSizeSlider->setValue(SADWindowSize);
            sBlocker.unblock();
        }

        if(minDisparitySlider->value() != minDisparity)
        {
            sBlocker.setObject(minDisparitySlider);
            sBlocker.block();
            minDisparitySlider->setValue(minDisparity);
            sBlocker.unblock();
        }

        if(numberOfDisparitiesSlider->value() != numberOfDisparities)
        {
            sBlocker.setObject(numberOfDisparitiesSlider);
            sBlocker.block();
            numberOfDisparitiesSlider->setValue(numberOfDisparities);
            sBlocker.unblock();
        }

        if(textureThresholdSlider->value() != textureThreshold)
        {
            sBlocker.setObject(textureThresholdSlider);
            sBlocker.block();
            textureThresholdSlider->setValue(textureThreshold);
            sBlocker.unblock();
        }

        if(uniquenessRatioSlider->value() != uniquenessRatio)
        {
            sBlocker.setObject(uniquenessRatioSlider);
            sBlocker.block();
            uniquenessRatioSlider->setValue(uniquenessRatio);
            sBlocker.unblock();
        }

        if(speckleWindowSizeSlider->value() != speckleWindowSize)
        {
            sBlocker.setObject(speckleWindowSizeSlider);
            sBlocker.block();
            speckleWindowSizeSlider->setValue(speckleWindowSize);
            sBlocker.unblock();
        }

        if(speckleRangeSlider->value() != speckleRange)
        {
            sBlocker.setObject(speckleRangeSlider);
            sBlocker.block();
            speckleRangeSlider->setValue(speckleRange);
            sBlocker.unblock();
        }

        if(disp12MaxDiffSlider->value() != disp12MaxDiff)
        {
            sBlocker.setObject(disp12MaxDiffSlider);
            sBlocker.block();
            disp12MaxDiffSlider->setValue(disp12MaxDiff);
            sBlocker.unblock();
        }

        if(static_cast<float>(averageTextureThresholdSpinBox->value()) != averageTextureThreshold)
        {
            sBlocker.setObject(averageTextureThresholdSpinBox);
            sBlocker.block();
            averageTextureThresholdSpinBox->setValue(static_cast<double>(averageTextureThreshold));
            sBlocker.unblock();
        }

        if(fullDPCheckBox->isChecked() != fullDP)
        {
            sBlocker.setObject(fullDPCheckBox);
            sBlocker.block();
            fullDPCheckBox->setChecked(fullDP);
            sBlocker.unblock();
        }

        if(sBlocker.hasObject())
        {
            emit valuesChanged();
        }
    }
}

void DisparityMapParametersWidget::enableRealtime()
{
    getRealTimeCheckBox()->setEnabled(true);
}

void DisparityMapParametersWidget::enableItems(int index)
{
    switch(index)
    {
        case 0:
        {
            averageTextureThresholdLabel->hide();
            averageTextureThresholdSpinBox->hide();
            fullDPCheckBox->hide();

            if(preFilterTypeComboBox->count() < 3)
            {
                preFilterTypeComboBox->addItem("NARROW_PRESET");
            }

            preFilterTypeLabel->show();
            preFilterTypeComboBox->show();
            preFilterSizeLabel->show();
            preFilterSizeSlider->show();
            preFilterSizeValueLabel->show();
            preFilterCapLabel->show();
            preFilterCapSlider->show();
            preFilterCapValueLabel->show();
            minDisparityLabel->show();
            minDisparitySlider->show();
            minDisparityValueLabel->show();
            textureThresholdLabel->show();
            textureThresholdSlider->show();
            textureThresholdValueLabel->show();
            uniquenessRatioLabel->show();
            uniquenessRatioSlider->show();
            uniquenessRatioValueLabel->show();
            speckleWindowSizeLabel->show();
            speckleWindowSizeSlider->show();
            speckleWindowSizeValueLabel->show();
            speckleRangeLabel->show();
            speckleRangeSlider->show();
            speckleRangeValueLabel->show();
            disp12MaxDiffLabel->show();
            disp12MaxDiffSlider->show();
            disp12MaxDiffValueLabel->show();
            break;
        }

        case 1:
        {
            preFilterTypeLabel->hide();
            preFilterTypeComboBox->hide();
            preFilterSizeLabel->hide();
            preFilterSizeSlider->hide();
            preFilterSizeValueLabel->hide();
            averageTextureThresholdLabel->hide();
            averageTextureThresholdSpinBox->hide();

            preFilterCapLabel->show();
            preFilterCapSlider->show();
            preFilterCapValueLabel->show();
            minDisparityLabel->show();
            minDisparitySlider->show();
            minDisparityValueLabel->show();
            textureThresholdLabel->show();
            textureThresholdSlider->show();
            textureThresholdValueLabel->show();
            uniquenessRatioLabel->show();
            uniquenessRatioSlider->show();
            uniquenessRatioValueLabel->show();
            speckleWindowSizeLabel->show();
            speckleWindowSizeSlider->show();
            speckleWindowSizeValueLabel->show();
            speckleRangeLabel->show();
            speckleRangeSlider->show();
            speckleRangeValueLabel->show();
            disp12MaxDiffLabel->show();
            disp12MaxDiffSlider->show();
            disp12MaxDiffValueLabel->show();

            fullDPCheckBox->show();
            break;
        }

        case 2:
        {
            preFilterTypeComboBox->removeItem(2);
            preFilterSizeLabel->hide();
            preFilterSizeSlider->hide();
            preFilterSizeValueLabel->hide();
            preFilterCapLabel->hide();
            preFilterCapSlider->hide();
            preFilterCapValueLabel->hide();
            minDisparityLabel->hide();
            minDisparitySlider->hide();
            minDisparityValueLabel->hide();
            textureThresholdLabel->hide();
            textureThresholdSlider->hide();
            textureThresholdValueLabel->hide();
            uniquenessRatioLabel->hide();
            uniquenessRatioSlider->hide();
            uniquenessRatioValueLabel->hide();
            speckleWindowSizeLabel->hide();
            speckleWindowSizeSlider->hide();
            speckleWindowSizeValueLabel->hide();
            speckleRangeLabel->hide();
            speckleRangeSlider->hide();
            speckleRangeValueLabel->hide();
            disp12MaxDiffLabel->hide();
            disp12MaxDiffSlider->hide();
            disp12MaxDiffValueLabel->hide();
            fullDPCheckBox->hide();

            averageTextureThresholdLabel->show();
            averageTextureThresholdSpinBox->show();
            break;
        }
    }
}

void DisparityMapParametersWidget::setAlgorithm(int)
{
    notify();
}

void DisparityMapParametersWidget::setPreFilterType(int)
{
    notify();
}

void DisparityMapParametersWidget::setPrefilterSize(int)
{
    notify();
}

void DisparityMapParametersWidget::setPreFilterCap(int)
{
    notify();
}

void DisparityMapParametersWidget::setSADWindowSize(int)
{
    notify();
}

void DisparityMapParametersWidget::setMinDisparity(int)
{
    notify();
}

void DisparityMapParametersWidget::setNumberOfDisparities(int)
{
    notify();
}

void DisparityMapParametersWidget::setTextureThreshold(int)
{
    notify();
}

void DisparityMapParametersWidget::setUniquenessRatio(int)
{
    notify();
}

void DisparityMapParametersWidget::setSpeckleWindowSize(int)
{
    notify();
}

void DisparityMapParametersWidget::setSpeckleRange(int)
{
    notify();
}

void DisparityMapParametersWidget::setDisp12MaxDiff(int)
{
    notify();
}

void DisparityMapParametersWidget::setAverageTextureThreshold(double)
{
    notify();
}

void DisparityMapParametersWidget::setFullDP(int)
{
    notify();
}
