#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    colorB = new ColorBWidget(this);
}

MainWindow::~MainWindow()
{

}
