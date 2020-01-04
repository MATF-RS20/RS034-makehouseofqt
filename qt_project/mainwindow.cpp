#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent)
{
    this->setWindowTitle("Kucni Pomocnik");
    drawingarea = new DrawingArea();

    QPalette p;
    p.setColor(QPalette::Background, Qt::white);
    drawingarea -> setPalette(p);
    drawingarea-> setGeometry(0,0,600,500);
    drawingarea-> setBackgroundRole(QPalette::Base);
    drawingarea -> setAutoFillBackground(true);
    drawingarea -> setMouseTracking(1);
    drawingarea -> setCursor(Qt::CrossCursor);
    drawingarea -> setWindowFlags(Qt::Window);

    buttonReset = new QPushButton;
    buttonReset ->setText("Obrisi trenutno crtanje");
    buttonComplete = new QPushButton;
    buttonComplete ->setText("Zavrsi nacrt");
    statusBar = new QLabel("status");
    buttonWallsView = new QPushButton;
    buttonWallsView->setText("3D prikaz zidova");
    buttonHouse = new QPushButton;
    buttonHouse->setText("3D setnja kroz kucu");
    this ->setUpdatesEnabled(true);

    clicked=true;

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget( drawingarea,  0, 0, 1, 4);
    mainLayout->addWidget(buttonComplete,1, 0, 1, 1,Qt::AlignLeft);
    mainLayout->addWidget(buttonReset,1, 1, 1, 1);
    mainLayout->addWidget(buttonWallsView, 1, 2, 1, 1);
    mainLayout->addWidget(buttonHouse,1, 3, 1, 1);
    setLayout(mainLayout);
    buttonReset->setEnabled(false);
    buttonComplete->setEnabled(false);
    buttonWallsView->setEnabled(false);
    buttonHouse->setEnabled(false);

    connect(this -> drawingarea, SIGNAL(have_points(int)), this, SLOT(setPointsnumber(int)),Qt::DirectConnection);
    connect(this->buttonReset, SIGNAL(clicked()), this ->drawingarea, SLOT(reset_drawing()), Qt::DirectConnection );
    connect(this->buttonReset, SIGNAL(clicked()), this, SLOT(reseting()));
    connect(this->buttonWallsView, SIGNAL(clicked(bool)), this, SLOT(on_buttonWallsView_clicked()));
    connect(this->buttonHouse, SIGNAL(clicked(bool)), this, SLOT(on_buttonHouse_clicked()));
    connect(this->buttonComplete, SIGNAL(clicked()), this ->drawingarea, SLOT(complete_drawing()), Qt::DirectConnection);
    connect(this ->drawingarea, SIGNAL(have_been_reseting(QString)),this->statusBar, SLOT(setText(QString)),Qt::AutoConnection);
    connect(this->drawingarea, SIGNAL(send_polygon_size(QString)), this->statusBar, SLOT(setText(QString )),Qt::DirectConnection);
    connect(this->drawingarea,SIGNAL(update_status_finish(QString)),this->statusBar,SLOT(update()),Qt::DirectConnection);
    connect(this->drawingarea,SIGNAL(update_status_finish(QString)),this->statusBar,SLOT(setText(QString)),Qt::DirectConnection);
    connect(this->drawingarea,SIGNAL(update_status(QString)),this->statusBar,SLOT(setText(QString)),Qt::DirectConnection);
    connect(this->drawingarea,SIGNAL(enableCompleteDrawing(bool)),this->buttonComplete,SLOT(setEnabled(bool)),Qt::DirectConnection);
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
this->buttonWallsView->setEnabled(true);
this->buttonHouse->setEnabled(true);
}

void MainWindow::reseting()
{
    buttonReset    -> setEnabled(true);
    buttonComplete -> setEnabled(true);
    update();
}

void MainWindow::on_buttonWallsView_clicked(){
    WallsModelView* wmv=new WallsModelView(drawingarea->getWall());

    if(clicked){
        wmv->show();
    }else{
        wmv->hide();
    }
    clicked=!clicked && true;
}

void MainWindow::on_buttonHouse_clicked(){

    QVector<Floor*> floors=this->drawingarea->getFloor();

    if(floors.size()>0){
        House *house= new House(floors);
        house->show();
    }else{
        QMessageBox::warning(this, tr("Upozorenje"),tr("Niste nacrtali ili niste sacuvali Vas rad"
                                                       "Molim Vas sacuvajte Vas rad klikom na taster N"));
    }


}
