#include <QCoreApplication>
#include <QFile>
#include "filechecker.h"
#include "consolelog.h"
#include <thread>
#include <QDebug>
#include <QDir>
#include <iostream>
#include <string>


int main(int argc, char *argv[])
{
    try {
        QCoreApplication a(argc, argv);

        QString currentExecDir = a.applicationDirPath();
//        QString file1 = "file.txt";
        QVector<QString> filesPaths = {"file.txt", "file1.txt"};
        for (auto i = 0; i < filesPaths.length(); i++) {
            filesPaths[i] = currentExecDir + '/' + filesPaths[i];
        }
//        FileChecker checker(currentExecDir + '/' + file1, &console);
        FileChecker& checker = FileChecker::getInstance();
        checker.setLog(&console);

        QObject::connect(&checker, &FileChecker::fileChanged, &checker, &FileChecker::printLog);
        QObject::connect(&checker, &FileChecker::fileAdded, &checker, &FileChecker::printLog);

        qDebug() << "Enter file name. Write 'stop' to end entering and start checking files. \n";
        std::string temp;
        std::getline(std::cin, temp);
        QString fileName;

        while (temp != "stop") {
            fileName = QString::fromStdString(temp);
            QString filePath = currentExecDir + '/' + fileName;
            bool wasAdded = checker.addFile(filePath);
            if (wasAdded) {
                qDebug() << "Location:" << filePath << "\n";
            }
            std::getline(std::cin, temp);
        }

        FileChecker& checker1 = FileChecker::getInstance();

        while (true && checker.isEmpty() == false) {
            checker1.checkFiles();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (checker.isEmpty()) {
            std::cout << "No files to check." << std::endl;
        }

        return a.exec();
    } catch (...) {
        throw std::runtime_error("main error");
    }
}
