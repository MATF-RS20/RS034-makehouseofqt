#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("Kucni Pomocnik");
    drawingarea=new DrawingArea();
    QPalette p;
    p.setColor(QPalette::Background,Qt::lightGray);
    drawingarea->setPalette(p);
    drawingarea->setGeometry(0,0,600,500);
    drawingarea->setBackgroundRole(QPalette::Base);
    drawingarea->setAutoFillBackground(true);
    drawingarea->setMouseTracking(1);
    drawingarea->setCursor(Qt::CrossCursor);
    drawingarea->setWindowFlags(Qt::Window);

    buttonReset=new QPushButton;
    buttonReset->setText("Obrisi trenutno nacrtano");
    buttonComplete=new QPushButton;
    buttonComplete->setText("Zavrsi nacrt");
    this ->setUpdatesEnabled(true);

    QGridLayout* mainLayout=new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(drawingarea,0,0,1,4);
    mainLayout->addWidget(buttonComplete,1,0,1,1);
    mainLayout->addWidget(buttonReset,1,1,1,1);
    setLayout(mainLayout);
    this->drawingarea->setFocus();

}

MainWindow::~MainWindow()
{
}
