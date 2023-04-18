#include "filechecker.h"
#include "consolelog.h"
#include <iostream>

FileChecker::FileChecker (const QFile &file) {
    this->m_exists = file.exists();
    if (this->m_exists) {
        this->m_size = file.size();
        ConsoleLog::fileFirstState(this->m_exists, this->m_size);
    } else {
        this->m_size = 0;
        ConsoleLog::fileFirstState(this->m_exists);
    }
}

void FileChecker::checkFile(const QFile &file) {
    if (file.exists() == this->m_exists) {
        if (file.exists() && file.size() != this->m_size) {
            ConsoleLog::onFileChange(file.size(), this->m_size);
            this->m_size = file.size();
        }
    } else {
        if (file.exists() == true) {
            ConsoleLog::onFileCreate(file.size());
            this->m_exists = true;
            this->m_size = file.size();
        } else {
            ConsoleLog::onFileDelete();
            this->m_exists = false;
            this->m_size = 0;
        }
    }
}
