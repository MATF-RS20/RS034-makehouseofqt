#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(isFinished()), parent, SLOT(changedParams()), Qt::DirectConnection);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::accept(){
    _height=this->ui->dsb_height->value();
    _thickness=this->ui->dsb_thick->value();
    emit isFinished();
    this->close();
}

float InputDialog::height() const{
    return _height;
}

float InputDialog::thickness()  const{
    return _thickness;
}
