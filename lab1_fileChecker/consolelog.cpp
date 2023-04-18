#include "consolelog.h"
#include <iostream>

void ConsoleLog::fileFirstState(bool exists, qint64 size) {
    if (exists) {
        std::cout << "File exists. Size: " << size << std::endl;
    } else {
        std::cout << "File doesn't exist." << std::endl;
    }
}

void ConsoleLog::onFileCreate(qint64 size) {
    std::cout << "\nFile created. Size: " << size << std::endl;
}

void ConsoleLog::onFileDelete() {
    std::cout << "\nFile deleted." << std::endl;
}

void ConsoleLog::onFileChange(qint64 newSize, qint64 oldSize) {
    std::cout << "\nFile changed. \nOld size: " << oldSize << "\nNew size: " << newSize << std::endl;
}
