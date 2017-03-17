/*!
 * \file parameterswidget.cpp
 * \brief Implementation of the methods of the ParametersWidget class declared in the parameterswidget.hpp header.
 * \author Hadrien Decoudras
 * \date 2017-01-14
 * \version 0.2
 */

#include "widgets/parameterswidget.hpp"

#include "parameters/parameters.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
ParametersWidget::ParametersWidget(const QString& title, QWidget* parent) : QWidget(parent), m(nullptr)
{
    QGridLayout* grid = new QGridLayout(this);
    setLayout(grid);

    QLabel* titleLabel = new QLabel(title, this);
    grid->addWidget(titleLabel, 0, 0, Qt::AlignLeft);

    applyPushButton = new QPushButton("Apply", this);
    realTimeCheckBox = new QCheckBox("Real Time Rendering", this);

    grid->addWidget(realTimeCheckBox, 1, 0, Qt::AlignLeft);
    grid->addWidget(applyPushButton, INT16_MAX, 2, Qt::AlignRight);

    connect(realTimeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setApply(int)));
    connect(realTimeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setRealTime(int)));
}

/**************************************************************
 **************************************************************
 *
 * Constructor.
 *
 **************************************************************/
ParametersWidget::ParametersWidget(const QString& title, QWidget* parent, Parameters* model) : QWidget(parent), m(model)
{
    QGridLayout* grid = new QGridLayout(this);
    setLayout(grid);

    QLabel* titleLabel = new QLabel(title, this);
    grid->addWidget(titleLabel, 0, 0, Qt::AlignLeft);

    applyPushButton = new QPushButton("Apply", this);
    realTimeCheckBox = new QCheckBox("Real Time Rendering", this);

    grid->addWidget(realTimeCheckBox, 1, 0, Qt::AlignLeft);
    grid->addWidget(applyPushButton, INT16_MAX, 1, Qt::AlignRight);

    connect(realTimeCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setApply(int)));
}

/**************************************************************
 **************************************************************
 *
 * Destructor.
 *
 **************************************************************/
ParametersWidget::~ParametersWidget() {}

/**************************************************************
 **************************************************************
 *
 * Attach Model.
 *
 **************************************************************/
void ParametersWidget::attach(Parameters* model)
{
    m = model;
}

/**************************************************************
 **************************************************************
 *
 * Gets model.
 *
 **************************************************************/
Parameters* ParametersWidget::model() const
{
    return m;
}

/**************************************************************
 **************************************************************
 *
 * Has model?
 *
 **************************************************************/
bool ParametersWidget::hasModel() const
{
    return (m != nullptr);
}

/**************************************************************
 **************************************************************
 *
 * Real time?
 *
 **************************************************************/
bool ParametersWidget::hasRealTime() const
{
    return realTimeCheckBox->isChecked();
}

/**************************************************************
 **************************************************************
 *
 * Gets apply button.
 *
 **************************************************************/
QPushButton* ParametersWidget::getApplyPushButton() const
{
    return applyPushButton;
}

/**************************************************************
 **************************************************************
 *
 * Gets real time checkbox
 *
 **************************************************************/
QCheckBox* ParametersWidget::getRealTimeCheckBox() const
{
    return realTimeCheckBox;
}

/**************************************************************
 **************************************************************
 *
 * Apply enable?
 *
 **************************************************************/
void ParametersWidget::setApply(int value)
{
    applyPushButton->setEnabled(value != Qt::Checked);
}


