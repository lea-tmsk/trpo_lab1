#ifndef CONSOLELOG_H
#define CONSOLELOG_H
#include <QFile>
#include "logger.h"

class ConsoleLog : public ILogger
{
public:
    void log(std::string msg) {
        std::cout << msg << std::endl;
    };
} console;

#endif // CONSOLELOG_H
