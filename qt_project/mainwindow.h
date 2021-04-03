#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawingarea.h"
#include "house.h"
#include "wallsmodelview.h"
#include <QEvent>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QtGui>
#include <QtWidgets>
class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);

  void mouseMoveEvent(QMouseEvent *e);

  QLabel *statusBar; // da uhvatimo signale koje nam salje drawarea. Ne
                     // prikazuje se na ekranu

  void changeStatus();

signals:

  void grabMouse();

public slots:

  void setPointsnumber();

signals:

  void setResetPoinst();
  void completePolygon();
  void enterEvent_();

private slots:

  void reseting();
  void on_buttonWallsView_clicked();
  void on_buttonHouse_clicked();

private:
  bool clicked;
  DrawingArea *drawingarea;
  QPushButton *buttonReset, *buttonComplete, *buttonWallsView, *buttonHouse;
  QColor selected_color;
};

#endif // MAINWINDOW_H
