#ifndef CUDARTNOTFOUNDEXCEPTION_HPP
#define CUDARTNOTFOUNDEXCEPTION_HPP

#include <exception>
#include <string>

class CudaRTNotFoundException : public std::exception
{
public:
    CudaRTNotFoundException(const char* string);
    ~CudaRTNotFoundException();

    const char* what() const throw();

private:
    std::string str;
};

#endif // CUDARTNOTFOUNDEXCEPTION_HPP
