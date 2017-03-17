#include "except/parametersdockwidgetgeneratorexception.hpp"

#include <sstream>

ParametersDockWidgetGeneratorException::ParametersDockWidgetGeneratorException(const char* string)
{
    std::ostringstream oss;
    oss << string;
    str = oss.str();
}

ParametersDockWidgetGeneratorException::~ParametersDockWidgetGeneratorException() {}

const char* ParametersDockWidgetGeneratorException::what() const throw()
{
    return str.c_str();
}
