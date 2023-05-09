#include "filechecker.h"
#include <iostream>

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
        FileInfo fileInfo = {filePath};
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
            FileInfo currentFileInfo = {*i};
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

FileChecker::~FileChecker() {
    if (m_files_info.length() > 0) {
        for (auto i = 0; i < m_files_info.length(); i++) {
            delete m_files_info[i].m_file;
        }
    }
}

void FileChecker::checkFiles() {
    for (auto i = 0; i < m_files_info.length(); i++) {
        if (m_files_info[i].m_file->exists() == m_files_info[i].m_exists) {
            if (m_files_info[i].m_exists && m_files_info[i].m_size != m_files_info[i].m_file->size()) {
                emit fileChanged("\nFile '" + m_files_info[i].m_file_name.toStdString() + "' changed. \nOld size: " + std::to_string(m_files_info[i].m_size) + " bytes" +
                                 + "\nNew size: " + std::to_string(m_files_info[i].m_file->size()) + " bytes");
                m_files_info[i].m_size = m_files_info[i].m_file->size();
            }
        } else {
            if (m_files_info[i].m_exists == true) {
                emit fileChanged("\nFile '" + m_files_info[i].m_file_name.toStdString() + "' deleted.");
                m_files_info[i].m_exists = false;
            } else {
                emit fileChanged("\nFile '" + m_files_info[i].m_file_name.toStdString() + "' created. Size: " + std::to_string(m_files_info[i].m_file->size()) + " bytes");
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
    int oldLength = this->m_files_info.length();

    this->m_files_info.append(FileInfo(filePath));

    if (oldLength == m_files_info.length()) {
        return false;
    }

    int index = this->m_files_info.length() - 1;

    if (m_files_info[index].m_exists == true) {
        emit fileAdded("File added. '" + m_files_info[index].m_file_name.toStdString() + "' exists. Size: " + std::to_string(m_files_info[index].m_size) + " bytes");
    } else {
        emit fileAdded("File added. '" + m_files_info[index].m_file_name.toStdString() + "' doesn't exist.");
    }
    return true;
}

bool FileChecker::removeFile(const QString filePath) {
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

void FileChecker::printLog(std::string msg) {
    m_log->log(msg);
}
