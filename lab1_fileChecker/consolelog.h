#ifndef CONSOLELOG_H
#define CONSOLELOG_H
#include <QFile>

class ConsoleLog
{
public:
    ConsoleLog() {};
    ~ConsoleLog() {};

    void static fileFirstState(bool exists, qint64 size = 0);
    void static onFileCreate(qint64 size);
    void static onFileDelete();
    void static onFileChange(qint64 newSize, qint64 oldSize);
};

#endif // CONSOLELOG_H
