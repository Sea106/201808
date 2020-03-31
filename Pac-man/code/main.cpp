#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv);
    srand((unsigned int)time(NULL));
    Widget w;
    w.show();

    return a.exec();
}
