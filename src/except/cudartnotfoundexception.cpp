#include "except/cudartnotfoundexception.hpp"

#include <sstream>

CudaRTNotFoundException::CudaRTNotFoundException(const char* string)
{
    std::ostringstream oss;
    oss << string;
    str = oss.str();
}

CudaRTNotFoundException::~CudaRTNotFoundException() {}


const char* CudaRTNotFoundException::what() const throw()
{
    return str.c_str();
}
