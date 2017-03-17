#ifndef PARAMETERSDOCKWIDGET_HPP
#define PARAMETERSDOCKWIDGET_HPP

#include <QDockWidget>

class ParameterObservers;

class ParametersDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    enum Generator
    {
        GEN_ERR = -1,
        GEN_BLUR = 0,
        GEN_SOBEL,
        GEN_CANNY,
        GEN_DISPARITY
    };

public:
    ParametersDockWidget(QWidget* parent = nullptr, ParameterObservers* obs = nullptr);
    ~ParametersDockWidget();

    Generator getGeneratorType() const;
    bool hasBeenGenerated() const;

signals:
    void applyButtonClicked();
    void realTimeCheckBoxChecked(bool);
    void valuesChanged();

private slots:
    void generate(int what);

private slots:
    void applyForwarder();
    void realTimeForwarder(int value);
    void valuesChangedForwarder();

private:
    void destroyGenerated();

private:
    int     method;

    bool    isGenerated;

    ParameterObservers* observers;
};

#endif // PARAMETERSDOCKWIDGET_H
