#include "filechecker.h"
#include <iostream>

FileChecker::FileChecker (const QFile &file, ILogger* log) {
    this->m_log = log;
    this->m_exists = file.exists();

    if (this->m_exists) {                                                                       //файл изначально существует
        this->m_size = file.size();
        this->m_log->log("\nFile exists. Size: " + std::to_string(file.size()));
    } else {                                                                                    //файл изначально не существует
        this->m_size = 0;
        this->m_log->log("\nFile doesn't exist.");
    }
}

void FileChecker::checkFile(const QFile &file) {
    if (file.exists() == this->m_exists) {                                                      //у файла не изменилось состояние: удален/существует
        if (file.exists() && file.size() != this->m_size) {                                     //если существует и изменился размер
            this->m_log->log("\nFile changed. \nOld size: " + std::to_string(this->m_size) + "\nNew size: " + std::to_string(file.size()));
            this->m_size = file.size();
        }
    } else {                                                                                    //если состояение изменилось
        if (file.exists() == true) {                                                            //если файл теперь существует
            this->m_log->log("\nFile created. Size: " + std::to_string(file.size()));
            this->m_exists = true;
            this->m_size = file.size();
        } else {                                                                                //если файл теперь не существует
            this->m_log->log("\nFile deleted");
            this->m_exists = false;
            this->m_size = 0;
        }
    }
}
