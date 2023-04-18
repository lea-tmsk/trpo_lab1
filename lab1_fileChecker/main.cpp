#include <QCoreApplication>
#include <QFile>
#include "filechecker.h"
#include <thread>
#include <QDebug>
#include <QDir>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString currentExecDir = a.applicationDirPath();
    qDebug() << "Enter file name: ";
    QString fileName;
    std::string temp;
    std::getline(std::cin, temp);
    std::cout << std::endl << temp << std::endl;
    fileName = QString::fromStdString(temp);
    QFile file(currentExecDir + '/' + fileName);
    qDebug() << "Location:" << currentExecDir + '/' + fileName;

    FileChecker checker(file);

    while (true) {
        checker.checkFile(file);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return a.exec();
}
