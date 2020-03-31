#include "mainwindow.h"
#include <QApplication>
#include<QString>
#include<ctime>
#include<fstream>
QString pl1;
QString pl2;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand((unsigned int)time(NULL));
    MainWindow w;
    w.show();
    return a.exec();
}
