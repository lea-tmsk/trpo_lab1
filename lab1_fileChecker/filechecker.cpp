#include "filechecker.h"
#include <iostream>
#include <QRegExp>

FileChecker::FileChecker(ILogger *log) {
    if (log != nullptr) {
        this->m_log = log;
    } else {
        //TODO: throw exception
    }
}

FileChecker::FileChecker(QVector<QString> filesPaths, ILogger* log) {
    if (filesPaths.length() > 0 && log != nullptr) {
        this->m_log = log;
        QVector<QString>::const_iterator i;
        for (i = filesPaths.constBegin(); i != filesPaths.constEnd(); ++i) {
            QFile currentFile(*i);
            FileInfo currentFileInfo = {*i, currentFile.exists(), currentFile.size()};
            this->m_files_info.append(currentFileInfo);
        }
    } else {
        return;
        //TODO
        //throw exception
    }
}

FileChecker::FileChecker(const QString filePath, ILogger* log) {
    if (filePath.length() > 0 && log != nullptr) {
        this->m_log = log;
        QFile file(filePath);
        FileInfo fileInfo = {filePath, file.exists(), file.size()};
        this->m_files_info.append(fileInfo);
    } else {
        return;
       //TODO: throw exception
    }
}

void FileChecker::checkFiles() {
    for (auto i = 0; i < m_files_info.length(); i++) {
        QString fileName = m_files_info[i].m_path.replace(QRegExp("(.+/.+/)"), "");
        if (m_files_info[i].m_file->exists() == m_files_info[i].m_exists) {
            if (m_files_info[i].m_exists && m_files_info[i].m_size != m_files_info[i].m_file->size()) {
                m_log->log("\nFile " + fileName.toStdString() + " changed. \nOld size: " + std::to_string(m_files_info[i].m_size) + "\nNew size: " + std::to_string(m_files_info[i].m_file->size()));
                m_files_info[i].m_size = m_files_info[i].m_file->size();
            }
        } else {
            if (m_files_info[i].m_exists == true) {
                m_log->log("\nFile " + fileName.toStdString() + " deleted.");
                m_files_info[i].m_exists = false;
            } else {
                m_log->log("\nFile " + fileName.toStdString() + " created. Size: " + std::to_string(m_files_info[i].m_file->size()));
                m_files_info[i].m_exists = true;
                m_files_info[i].m_size = m_files_info[i].m_file->size();
            }
        }
    }
}

bool FileChecker::addFile(const QString filePath) {
    if (filePath == "") {
        return false;
    }
    QFile file(filePath);
    QString fileName = filePath;
    fileName = fileName.replace(QRegExp("(.+/.+/)"), "");
    m_files_info.append(FileInfo {filePath, file.exists(), file.size()});
    if (file.exists()) {
        m_log->log("Added file " + fileName.toStdString() + " exists. Size: " + std::to_string(file.size()));
    } else {
        m_log->log("Added file " + fileName.toStdString() + " doesn't exist.");
    }
    return true;
}

bool FileChecker::removeFile(const QString filePath)
{
    if (filePath == "") {
        return false;
    }
    for (auto i = 0; i < m_files_info.length(); i++) {
        if (m_files_info[i].m_path == filePath) {
            m_files_info.erase(m_files_info.begin() + i);
            return true;
        }
    }
    return false;
}

bool FileChecker::isEmpty() {
    return this->m_files_info.length() == 0;
}
