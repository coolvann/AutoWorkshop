#include "ui/windows/MainWindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "main started!";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qDebug() << "MainWindow constructed";

    return a.exec();
}
