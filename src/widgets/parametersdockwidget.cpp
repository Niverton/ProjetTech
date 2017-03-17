#include "widgets/parametersdockwidget.hpp"

#include "parameters/parameterobservers.hpp"
#include "parameters/blurparameters.hpp"
#include "widgets/blurparameterswidget.hpp"
#include "widgets/sobelparameterswidget.hpp"
#include "widgets/cannyparameterswidget.hpp"
#include "widgets/disparitymapparameterswidget.hpp"
#include "except/parametersdockwidgetgeneratorexception.hpp"

#include <QFile>
#include <QPushButton>
#include <QCheckBox>

ParametersDockWidget::ParametersDockWidget(QWidget* parent, ParameterObservers* obs) : QDockWidget(parent), method(-1), isGenerated(false)
{
    observers = obs;

    QFile file(":/styles/parametersdockwidget/parametersdockwidget.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    QString styleSheet = file.readAll();
    setStyleSheet(styleSheet);
    file.close();

    QString s = "Parameters";

    QFontMetrics fm = QFontMetrics(s);
    setMinimumWidth(fm.width(s, s.count()) + 20);

    setWindowTitle(s);
    setAttribute(Qt::WA_DeleteOnClose);
}

ParametersDockWidget::~ParametersDockWidget() {}

ParametersDockWidget::Generator ParametersDockWidget::getGeneratorType() const
{
    return static_cast<ParametersDockWidget::Generator>(method);
}

bool ParametersDockWidget::hasBeenGenerated() const
{
    return isGenerated;
}

void ParametersDockWidget::generate(int what)
{
    if(method == what)
    {
        return;
    }
    else
    {
        if(isGenerated)
        {
            destroyGenerated();
            update();
        }
    }

    method = what;
    ParametersDockWidget::Generator g = static_cast<ParametersDockWidget::Generator>(what);

    switch(g)
    {
        case ParametersDockWidget::Generator::GEN_BLUR:
        {
            Parameters* model = observers->getObserver(ParameterObservers::Observer::OBS_BLUR);
            BlurParametersWidget* view = new BlurParametersWidget(this, model);
            model->attach(view);
            setWidget(view);

            connect(view->getApplyPushButton(), SIGNAL(clicked(bool)), this, SLOT(applyForwarder()));
            connect(view->getRealTimeCheckBox(), SIGNAL(stateChanged(int)), this, SLOT(realTimeForwarder(int)));
            connect(view, SIGNAL(valuesChanged()), this, SLOT(valuesChangedForwarder()));

            break;
        }

        case ParametersDockWidget::Generator::GEN_SOBEL:
        {
            Parameters* model = observers->getObserver(ParameterObservers::Observer::OBS_SOBEL);
            SobelParametersWidget* view = new SobelParametersWidget(this, model);
            model->attach(view);
            setWidget(view);

            connect(view->getApplyPushButton(), SIGNAL(clicked(bool)), this, SLOT(applyForwarder()));
            connect(view->getRealTimeCheckBox(), SIGNAL(stateChanged(int)), this, SLOT(realTimeForwarder(int)));
            connect(view, SIGNAL(valuesChanged()), this, SLOT(valuesChangedForwarder()));

            break;
        }

        case ParametersDockWidget::Generator::GEN_CANNY:
        {
            Parameters* model = observers->getObserver(ParameterObservers::Observer::OBS_CANNY);
            CannyParametersWidget* view = new CannyParametersWidget(this, model);
            model->attach(view);
            setWidget(view);

            connect(view->getApplyPushButton(), SIGNAL(clicked(bool)), this, SLOT(applyForwarder()));
            connect(view->getRealTimeCheckBox(), SIGNAL(stateChanged(int)), this, SLOT(realTimeForwarder(int)));
            connect(view, SIGNAL(valuesChanged()), this, SLOT(valuesChangedForwarder()));

            break;
        }

        case ParametersDockWidget::Generator::GEN_DISPARITY:
        {
            Parameters* model = observers->getObserver(ParameterObservers::Observer::OBS_DISPARITY);
            DisparityMapParametersWidget* view = new DisparityMapParametersWidget(this, model);
            model->attach(view);
            setWidget(view);

            connect(view->getApplyPushButton(), SIGNAL(clicked(bool)), this, SLOT(applyForwarder()));
            connect(view->getRealTimeCheckBox(), SIGNAL(stateChanged(int)), this, SLOT(realTimeForwarder(int)));
            connect(view, SIGNAL(valuesChanged()), this, SLOT(valuesChangedForwarder()));

            break;
        }

        default:
        {
            std::string err = "Invalid Dock Widget Generator: " + std::to_string(method);
            throw ParametersDockWidgetGeneratorException(err.c_str());
        }
    }

    isGenerated = true;
}

void ParametersDockWidget::applyForwarder()
{
    emit applyButtonClicked();
}

void ParametersDockWidget::realTimeForwarder(int value)
{
    emit realTimeCheckBoxChecked(value == Qt::Checked);
}

void ParametersDockWidget::valuesChangedForwarder()
{
    emit valuesChanged();
}

void ParametersDockWidget::destroyGenerated()
{
    widget()->deleteLater();
}
