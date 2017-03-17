#ifndef PARAMETERSDOCKWIDGETGENERATOREXCEPTION_HPP
#define PARAMETERSDOCKWIDGETGENERATOREXCEPTION_HPP

#include <exception>
#include <string>

class ParametersDockWidgetGeneratorException : public std::exception
{
public:
    ParametersDockWidgetGeneratorException(const char* string);
    ~ParametersDockWidgetGeneratorException();

    const char * what() const throw();

private:
    std::string str;
};

#endif // PARAMETERSDOCKWIDGETGENERATOREXCEPTION_H
