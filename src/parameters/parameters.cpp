#include "parameters/parameters.hpp"

#include <QWidget>

Parameters::Parameters() : realTime(false), v(nullptr) {}

Parameters::Parameters(QWidget* view) : realTime(false), v(view) {}

Parameters::~Parameters() {}

void Parameters::attach(QWidget* view)
{
    v = view;
}

QWidget* Parameters::view() const
{
    return v;
}

bool Parameters::isAttached() const
{
    return (v != nullptr);
}

void Parameters::setRealTime(bool value)
{
    realTime = value;
}

bool Parameters::getRealTime() const
{
    return realTime;
}
