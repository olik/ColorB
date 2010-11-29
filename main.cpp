#include <QtGui/QApplication>
#include "mainwindow.h"

#include "iostream"
#include "ColorB/CBManager.h"

int main(int argc, char *argv[])
{
    CBManager manager;
    std::cout << manager.ToString();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
