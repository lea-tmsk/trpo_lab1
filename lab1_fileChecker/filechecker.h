#ifndef FILECHECKER_H
#define FILECHECKER_H
#include <QFile>
#include "logger.h"

class FileChecker
{
public:
    FileChecker(const QFile &file, ILogger* log);
    ~FileChecker() {};

    void checkFile(const QFile &file);
    enum States {
        deleted,
        created,
        changed,
        same,
        exists,
        doesNotExist
    };

private:
    bool m_exists;
    qint64 m_size;
    ILogger* m_log;
};

#endif // FILECHECKER_H
