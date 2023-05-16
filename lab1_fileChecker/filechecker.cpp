#include "filechecker.h"
#include <iostream>

FileChecker* FileChecker::m_instance = nullptr;

FileChecker::FileChecker(ILogger *log) {
    if (log != nullptr) {
        this->m_log = log;
    } else {
        throw std::runtime_error("log is nullptr");
    }
}

FileChecker::FileChecker(const QString filePath, ILogger* log) {
    if (filePath != "" && log != nullptr) {
        this->m_log = log;
        FileInfo fileInfo(filePath);
        this->m_files_info.append(fileInfo);
    } else {
        if (log == nullptr) {
            throw std::runtime_error("log is nullptr");
        }
    }
}

FileChecker::FileChecker(QVector<QString> filesPaths, ILogger* log) {
    if (log != nullptr) {
        this->m_log = log;
        for (int i = 0; i < filesPaths.length(); i++) {
            FileInfo currentFileInfo(filesPaths[i]);
            m_files_info.append(currentFileInfo);
        }
    } else {
        throw std::runtime_error("log is nullptr");
    }
}

FileChecker::~FileChecker() {
    if (m_log != nullptr) {
        delete m_log;
        m_log = nullptr;
    }
}

void FileChecker::checkFiles() {
    for (auto i = 0; i < m_files_info.length(); i++) {
        QFileInfo file(m_files_info[i].m_path);
        if (file.exists() == m_files_info[i].m_exists) {
            if (m_files_info[i].m_exists && m_files_info[i].m_size != file.size()) {
                emit fileChanged("\nFile '" + m_files_info[i].m_file_name.toStdString() + "' changed. \nOld size: " + std::to_string(m_files_info[i].m_size) + " bytes" +
                                 + "\nNew size: " + std::to_string(file.size()) + " bytes");
                m_files_info[i].m_size = file.size();
            }
        } else {
            if (m_files_info[i].m_exists == true) {
                emit fileChanged("\nFile '" + m_files_info[i].m_file_name.toStdString() + "' deleted.");
                m_files_info[i].m_exists = false;
            } else {
                emit fileChanged("\nFile '" + m_files_info[i].m_file_name.toStdString() + "' created. Size: " + std::to_string(file.size()) + " bytes");
                m_files_info[i].m_exists = true;
                m_files_info[i].m_size = file.size();
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
