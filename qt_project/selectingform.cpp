#include "selectingform.h"
#include "ui_selectingform.h"

SelectingForm::SelectingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectingForm)
{
    ui->setupUi(this);


}

SelectingForm::~SelectingForm()
{
    delete ui;
}

void SelectingForm::on_pushButton_clicked(){
    if(this->ui->radioButton->isChecked())
        emit sendingChoice(0);
    else if(this->ui->radioButton_2->isChecked())
        emit sendingChoice(1);
    else if(this->ui->radioButton_3->isChecked())
        emit sendingChoice(2);
    else if(this->ui->radioButton_4->isChecked())
        emit sendingChoice(3);

    this->close();
}

void SelectingForm::on_pushButton_2_clicked(){
    this->close();
}
