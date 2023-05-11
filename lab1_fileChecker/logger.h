#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>

class ILogger
{
public:
    virtual ~ILogger() {};
    virtual void log(std::string msg) = 0;
};

#endif // LOGGER_H
