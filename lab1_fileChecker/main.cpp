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
    qDebug() << "Enter file name: ";                                        //спрашиваем у пользователя имя файла
    QString fileName;
    std::string temp;
    std::getline(std::cin, temp);
    std::cout << std::endl << temp << std::endl;
    fileName = QString::fromStdString(temp);
    QFile file(currentExecDir + '/' + fileName);
    qDebug() << "Location:" << currentExecDir + '/' + fileName;             //полный путь до файла

    FileChecker checker(file, &console);                                    //создаем объект класса, который будет проверять состояние файла по указанному пути, с выбором метода логирования

    while (true) {                                                          //в цикле каждые 100мс проверяем состояние файла
        checker.checkFile(file);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return a.exec();
}
