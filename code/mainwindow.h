#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QPushButton>
#include <QGridLayout>
#include"drawingarea.h"


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    DrawingArea* drawingarea;
    QPushButton* buttonReset,*buttonComplete;
};

#endif // MAINWINDOW_H
