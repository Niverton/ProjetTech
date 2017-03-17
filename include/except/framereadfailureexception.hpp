#ifndef FRAMEREADFAILUREEXCEPTION_HPP
#define FRAMEREADFAILUREEXCEPTION_HPP

#include <exception>
#include <string>

class FrameReadFailureException : public std::exception
{
public:
    FrameReadFailureException(const char* string);
    ~FrameReadFailureException();

    const char* what() const throw();

private:
    std::string str;
};

#endif // FRAMEREADFAILUREEXCEPTION_HPP
