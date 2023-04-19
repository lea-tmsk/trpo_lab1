#include "filechecker.h"
#include <iostream>
#include <QRegExp>

FileChecker::FileChecker(ILogger *log) {
    if (log != nullptr) {
        this->m_log = log;
    } else {
        throw std::runtime_error("log is nullptr");
    }
}

FileChecker::FileChecker(const QString filePath, ILogger* log) {
    if (filePath.length() > 0 && log != nullptr) {
        this->m_log = log;
        QFile file(filePath);
        FileInfo fileInfo = {filePath, file.exists(), file.size()};
        this->m_files_info.append(fileInfo);
    } else {
        if (filePath == nullptr) {
            throw std::runtime_error("filePath is nullptr");
        } else if (filePath.length() == 0) {
            throw std::runtime_error("filePath is an empty string");
        } else {
            throw std::runtime_error("log is nullptr");
        }
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
        if (filesPaths.length() == 0) {
            throw std::runtime_error("QVector is empty");
        } else {
            throw std::runtime_error("log is nullptr");
        }
    }
}

void FileChecker::checkFiles() {
    for (auto i = 0; i < m_files_info.length(); i++) {
        QString fileName = m_files_info[i].m_path.replace(QRegExp("(.+/.+/)"), "");
        if (m_files_info[i].m_file->exists() == m_files_info[i].m_exists) {
            if (m_files_info[i].m_exists && m_files_info[i].m_size != m_files_info[i].m_file->size()) {
                emit fileChanged("\nFile '" + fileName.toStdString() + "' changed. \nOld size: " + std::to_string(m_files_info[i].m_size) + " bytes" +
                                 + "\nNew size: " + std::to_string(m_files_info[i].m_file->size()) + " bytes");
                m_files_info[i].m_size = m_files_info[i].m_file->size();
            }
        } else {
            if (m_files_info[i].m_exists == true) {
                emit fileChanged("\nFile '" + fileName.toStdString() + "' deleted.");
                m_files_info[i].m_exists = false;
            } else {
                emit fileChanged("\nFile '" + fileName.toStdString() + "' created. Size: " + std::to_string(m_files_info[i].m_file->size()) + " bytes");
                m_files_info[i].m_exists = true;
                m_files_info[i].m_size = m_files_info[i].m_file->size();
            }
        }
    }
}

bool FileChecker::addFile(const QString filePath) {
    QString fileName = filePath;
    fileName = fileName.replace(QRegExp("(.+/.+/)"), "");

    if (fileName == "") {
        return false;
    }
    QFile file(filePath);
    try {
        m_files_info.append(FileInfo {filePath, file.exists(), file.size()});
        if (file.exists()) {
            m_log->log("File added. '" + fileName.toStdString() + "' exists. Size: " + std::to_string(file.size()) + " bytes");
        } else {
            m_log->log("File added. '" + fileName.toStdString() + "' doesn't exist.");
        }
    }  catch (const std::exception& ex) {
        return false;
    }
    return true;
}

bool FileChecker::removeFile(const QString filePath) {
    QString fileName = filePath;
    fileName = fileName.replace(QRegExp("(.+/.+/)"), "");

    if (fileName == "") {
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

void FileChecker::printLog(std::string msg) {
    m_log->log(msg);
}
