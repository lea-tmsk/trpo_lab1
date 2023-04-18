#ifndef FILECHECKER_H
#define FILECHECKER_H
#include <QFile>

class FileChecker
{
public:
    FileChecker() {};
    FileChecker(const QFile &file);
    ~FileChecker() {};

    void checkFile(const QFile &file);
private:
    bool m_exists;
    qint64 m_size;
};

#endif // FILECHECKER_H
