#ifndef CUDARTRESOLVEEXCEPTION_H
#define CUDARTRESOLVEEXCEPTION_H

#include <exception>
#include <string>

class CudaRTResolveException
{
public:
    CudaRTResolveException(const char* string);
    ~CudaRTResolveException();

    const char* what() const throw();

private:
    std::string str;
};

#endif // CUDARTRESOLVEEXCEPTION_H
