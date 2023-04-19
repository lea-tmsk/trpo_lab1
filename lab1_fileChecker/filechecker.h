#ifndef FILECHECKER_H
#define FILECHECKER_H
#include <QFile>
#include <QObject>
#include "logger.h"

class FileChecker : public QObject
{
Q_OBJECT public:
    FileChecker() {};
    FileChecker(ILogger* log);
    FileChecker(const QString filePath, ILogger* log);
    FileChecker(QVector<QString> filesPaths, ILogger* log);
    ~FileChecker() {};

    void checkFiles();
    bool addFile(const QString filePath);
    bool removeFile(const QString filePath);
    bool isEmpty();
public slots:
    void printLog(std::string msg);

signals:
    void fileChanged(std::string msg);

private:
    struct FileInfo {
    public:
        FileInfo(QString path, bool exists, qint64 size) : m_path{path}, m_exists{exists}, m_size{size} {
            m_file->setFileName(path);
        };
        QString m_path;
        QFile *m_file = new QFile();
        bool m_exists;
        qint64 m_size;
    };

    QVector<FileInfo> m_files_info;
    ILogger* m_log;
};

#endif // FILECHECKER_H
