#ifndef FILECHECKER_H
#define FILECHECKER_H
#include <QFileInfo>
#include <QObject>
#include "logger.h"

class FileChecker : public QObject
{
Q_OBJECT public:
    static FileChecker* getInstance() {
        if (!m_instance) {
            return nullptr;
        }
        return m_instance;
    }
    static FileChecker* getInstance(ILogger* log) {
        if (!m_instance) {
            m_instance = new FileChecker(log);
        }
        return m_instance;
    }
    static FileChecker* getInstance(const QString filePath, ILogger* log) {
        if (!m_instance) {
            m_instance = new FileChecker(filePath, log);
        }
        return m_instance;
    }
    static FileChecker* getInstance(QVector<QString> filesPaths, ILogger* log) {
        if (!m_instance) {
            m_instance = new FileChecker(filesPaths, log);
        }
        return m_instance;
    }

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
    FileChecker(ILogger* log);
    FileChecker(const QString filePath, ILogger* log);
    FileChecker(QVector<QString> filesPaths, ILogger* log);
    ~FileChecker();

    FileChecker(const FileChecker&);
    FileChecker& operator=(FileChecker&);

    struct FileInfo {
    public:
        FileInfo(QString path) {
            QFileInfo temp(path);
            m_path = path;
            m_file_name = temp.fileName();
            m_exists = temp.exists();
            m_size = temp.size();
        }
        ~FileInfo() {};
        QString m_path;
        QString m_file_name;
        bool m_exists;
        qint64 m_size;
    };
    static FileChecker* m_instance;// = nullptr;
    QVector<FileInfo> m_files_info;
    ILogger* m_log;
};

#endif // FILECHECKER_H
