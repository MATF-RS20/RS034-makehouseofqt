#include "mainwindow.h"
#include <QtGui>
#include <QApplication>


int main( int argc, char **argv )
{
  QApplication app( argc, argv );

  MainWindow mainwindow;
  mainwindow.setMouseTracking(1);
  mainwindow.setGeometry(0,0,880,680);
  mainwindow.show();

  return app.exec();
}
