#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(0,0,800,600);
    w.show();
    a.setActiveWindow(&w);

    return a.exec();
}
