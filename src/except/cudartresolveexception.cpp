#include "except/cudartresolveexception.hpp"

#include <sstream>

CudaRTResolveException::CudaRTResolveException(const char* string)
{
    std::ostringstream oss;
    oss << string;
    str = oss.str();
}

CudaRTResolveException::~CudaRTResolveException() {}

const char* CudaRTResolveException::what() const throw()
{
    return str.c_str();
}
