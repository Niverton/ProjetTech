#include "except/filenotfoundexception.hpp"

#include <sstream>

FileNotFoundException::FileNotFoundException(const char* string)
{
    std::ostringstream oss;
    oss << string;
    str = oss.str();
}

FileNotFoundException::~FileNotFoundException() {}

const char* FileNotFoundException::what() const throw()
{
    return str.c_str();
}
