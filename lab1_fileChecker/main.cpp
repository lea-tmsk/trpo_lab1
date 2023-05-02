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
    QCoreApplication a(argc, argv);

    QString currentExecDir = a.applicationDirPath();
    FileChecker checker(&console);
    QObject::connect(&checker, SIGNAL(fileChanged(std::string)), &checker, SLOT(printLog(std::string)));
    QObject::connect(&checker, SIGNAL(fileAdded(std::string)), &checker, SLOT(printLog(std::string)));

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

    while (true && checker.isEmpty() == false) {
        checker.checkFiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (checker.isEmpty()) {
        std::cout << "No files to check." << std::endl;
    }

    return a.exec();
}
