#include "ui/windows/MainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    qDebug() << "main started!";
    QApplication a(argc, argv);
    // a.setStyle(QStyleFactory::create("Fusion"));
    MainWindow w;
    w.show();
    qDebug() << "MainWindow constructed";

    return a.exec();
}
