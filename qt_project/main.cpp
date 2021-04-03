#include "mainwindow.h"
#include <QApplication>
#include <QtGui>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  MainWindow mainwindow;
  mainwindow.setMouseTracking(true);
  mainwindow.setGeometry(0, 0, 880, 680);
  mainwindow.show();

  return QApplication::exec();
}
