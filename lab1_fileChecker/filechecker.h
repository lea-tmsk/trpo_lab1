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
    ~FileChecker();

    void checkFiles();
    bool addFile(const QString filePath);
    bool removeFile(const QString filePath);
    bool isEmpty();
public slots:
    void printLog(std::string msg);

signals:
    void fileChanged(std::string msg);
    void fileAdded(std::string msg);

private:
    struct FileInfo {
    public:
        FileInfo(QString path) {
            m_file = new QFile(path);
            m_file_name = path.replace(QRegExp("(.+/.+/)"), "");
            m_path = path;
            m_exists = m_file->exists();
            m_size = m_file->exists() == true ? m_file->size() : 0;
        }
        ~FileInfo() {};
        QString m_path;
        QString m_file_name;
        QFile *m_file;
        bool m_exists;
        qint64 m_size;
    };

    QVector<FileInfo> m_files_info;
    ILogger* m_log;
};

#endif // FILECHECKER_H
