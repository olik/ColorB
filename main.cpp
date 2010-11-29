#include <QtGui/QApplication>
#include "mainwindow.h"

#include "iostream"
#include "ColorB/CBManager.h"
#include "ColorBTest/CBTestManager.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "Windows-1251" ) );
    CBTestManager testData;
    QTest::qExec( &testData );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
