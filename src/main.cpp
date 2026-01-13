#include "ui/MainWindow.h"
#include "logger/Log.h"
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    qCInfo(logApp) << "main started!";
    QApplication a(argc, argv);
    // a.setStyle(QStyleFactory::create("Fusion"));
    MainWindow w;
    w.show();
    qCInfo(logApp) << "MainWindow constructed";

    return a.exec();
}
