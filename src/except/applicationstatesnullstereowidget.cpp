#include "except/applicationstatesnullstereowidget.hpp"

#include <sstream>

ApplicationStatesNullStereoWidgetException::ApplicationStatesNullStereoWidgetException(const char* string)
{
    std::ostringstream oss;
    oss << string;
    str = oss.str();
}

ApplicationStatesNullStereoWidgetException::~ApplicationStatesNullStereoWidgetException() {}

const char* ApplicationStatesNullStereoWidgetException::what() const throw()
{
    return str.c_str();
}
