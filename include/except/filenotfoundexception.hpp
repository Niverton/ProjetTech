#ifndef FILENOTFOUNDEXCEPTION_HPP
#define FILENOTFOUNDEXCEPTION_HPP

#include <exception>
#include <string>

class FileNotFoundException : public std::exception
{
public:
    FileNotFoundException(const char* string);
    ~FileNotFoundException();

    const char* what() const throw();

private:
    std::string str;
};

#endif // FILENOTFOUNDEXCEPTION_HPP
