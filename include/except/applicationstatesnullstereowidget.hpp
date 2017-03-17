#ifndef APPLICATIONSTATENULLSTEREOWIDGETEXCEPTION_HPP
#define APPLICATIONSTATENULLSTEREOWIDGETEXCEPTION_HPP

#include <exception>
#include <string>

class ApplicationStatesNullStereoWidgetException : public std::exception
{
public:
    ApplicationStatesNullStereoWidgetException(const char* string);
    ~ApplicationStatesNullStereoWidgetException();

    const char* what() const throw();

private:
    std::string str;
};

#endif // APPLICATIONSTATENULLSTEREOWIDGETEXCEPTION_HPP
