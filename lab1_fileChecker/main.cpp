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

    QString currentExecDir = a.applicationDirPath();                        //файл ищем в директории проекта
    FileChecker checker(&console);                                          //создаем объект класса с выбором метода логирования

    qDebug() << "Enter file name. Write 'stop' to end. \n";                 //спрашиваем у пользователя имя файла
    std::string temp;
    std::getline(std::cin, temp);
    QString fileName;

    while (temp != "stop") {
        std::cout << std::endl << temp << std::endl;
        fileName = QString::fromStdString(temp);
        QString filePath = currentExecDir + '/' + fileName;
        bool wasAdded = checker.addFile(filePath);
        if (wasAdded) {
            qDebug() << "Location:" << currentExecDir + '/' + fileName;     //полный путь до файла
        }
        std::getline(std::cin, temp);
    }

    while (true && checker.isEmpty() == false) {                                                          //в цикле каждые 100мс проверяем состояние файла
        checker.checkFiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (checker.isEmpty()) {
        std::cout << "No files to check" << std::endl;
    }

    return a.exec();
}
