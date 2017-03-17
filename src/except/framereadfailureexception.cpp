#include "except/framereadfailureexception.hpp"

#include <sstream>

FrameReadFailureException::FrameReadFailureException(const char* string)
{
    std::ostringstream oss;
    oss << string;
    str = oss.str();
}

FrameReadFailureException::~FrameReadFailureException() {}

const char* FrameReadFailureException::what() const throw()
{
    return str.c_str();
}
