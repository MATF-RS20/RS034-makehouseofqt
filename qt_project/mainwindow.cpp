#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    this->setWindowTitle("Kucni Pomocnik");
    drawingarea = new DrawingArea();
    QPalette p;
    p.setColor(QPalette::Background, Qt::white);
    drawingarea -> setPalette(p);
    drawingarea->setGeometry(0,0,600,500);
    drawingarea->setBackgroundRole(QPalette::Base);
    drawingarea -> setAutoFillBackground(true);
    drawingarea -> setMouseTracking(1);
    drawingarea -> setCursor(Qt::CrossCursor);
    drawingarea -> setMouseTracking(1);
    drawingarea -> setWindowFlags(Qt::Window);

    buttonReset = new QPushButton;
    buttonReset ->setText("Obrisi trenutno nacrtano");
    buttonComplete = new QPushButton;
    buttonComplete ->setText("Zavrsi nacrt");
    statusBar = new QLabel("status");
    this ->setUpdatesEnabled(true);

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget( drawingarea,  0, 0, 1, 4);
    mainLayout->addWidget(buttonComplete,1, 0, 1, 1,Qt::AlignLeft);
    mainLayout->addWidget(buttonReset,1, 1, 1, 1);
    setLayout(mainLayout);
    buttonReset->setEnabled(false);
    buttonComplete->setEnabled(false);

    connect(this -> drawingarea, SIGNAL(releaseMouse()), this, SLOT(grabMouse()),Qt::DirectConnection);
    connect(this -> drawingarea, SIGNAL(have_points(int)), this, SLOT(setPointsnumber(int)),Qt::DirectConnection);
    connect(this->buttonReset, SIGNAL(clicked()), this ->drawingarea, SLOT(reset_drawing()), Qt::DirectConnection );
    connect(this->buttonReset, SIGNAL(clicked()), this, SLOT(reseting()));
    connect(this->buttonComplete, SIGNAL(clicked()), this ->drawingarea, SLOT(complete_drawing()), Qt::DirectConnection);
    connect(this ->drawingarea, SIGNAL(have_been_reseting(QString)),this->statusBar, SLOT(setText(QString)),Qt::AutoConnection);
    connect(this->drawingarea, SIGNAL(send_polygon_size(QString)), this->statusBar, SLOT(setText(QString )),Qt::DirectConnection);
    connect(this->drawingarea,SIGNAL(update_status_finish(QString)),this->statusBar,SLOT(update()),Qt::DirectConnection);
    connect(this->drawingarea,SIGNAL(update_status_finish(QString)),this->statusBar,SLOT(setText(QString)),Qt::DirectConnection);
    connect(this->drawingarea,SIGNAL(update_status(QString)),this->statusBar,SLOT(setText(QString)),Qt::DirectConnection);
    connect(this->drawingarea,SIGNAL(enableCompleteDrawing(bool)),this->buttonComplete,SLOT(setEnabled(bool)),Qt::DirectConnection);
    connect(this->drawingarea, SIGNAL(leaveEvent(QMouseEvent)),this,SLOT(showNormal()),Qt::DirectConnection );
    connect(this,SIGNAL(grabMouse()),this->drawingarea,SLOT(changeOnMouse()),Qt::DirectConnection);
    connect(this->drawingarea, SIGNAL(HoverLeave(QPointF&,QPointF)), this -> drawingarea, SLOT(changeOnMouse()), Qt::DirectConnection);
    connect(this,SIGNAL(enterEvent_()),this->drawingarea, SLOT(changeOnMouse()),Qt::DirectConnection);
    connect(this -> drawingarea, SIGNAL(fail_to_add_peak(QString)), this->statusBar, SLOT(setText(QString)),Qt::DirectConnection);

    this->drawingarea->setFocus();
}

void MainWindow::mouseMoveEvent(QMouseEvent * e)
{

    Q_UNUSED(e);
     setCursor(Qt::ArrowCursor);
     this->update();
     emit enterEvent_();
     this->drawingarea->setFocus();

}


void MainWindow::setPointsnumber(int)
{
this->buttonReset   ->setEnabled(true);
this->buttonComplete->setEnabled(true);

}

void MainWindow::reseting()
{
    buttonReset    -> setEnabled(false);
    buttonComplete -> setEnabled(false);
    statusBar      -> setText(tr("Please paint new Polygon"));
    update();
}
