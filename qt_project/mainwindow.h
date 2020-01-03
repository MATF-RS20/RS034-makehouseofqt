#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtGui>
#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include <QEvent>
#include <QtWidgets>
#include "drawingarea.h"
#include "wallsmodelview.h"
#include "house.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent * e);

    QLabel* statusBar; //da uhvatimo signale koje nam salje drawarea. Ne prikazuje se na ekranu


    void changeStatus();



signals:

    void grabMouse();

public slots:

    void setPointsnumber(int);


signals:

    void setResetPoinst( );
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
