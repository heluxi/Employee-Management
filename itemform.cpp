#include "itemform.h"
#include "ui_itemform.h"

itemForm::itemForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::itemForm)
{
    ui->setupUi(this);
}

itemForm::~itemForm()
{
    delete ui;
}

void itemForm::setStaffInfo(int id, int age,QString name, QString addr, int salary)
{
    ui->idLable->setText(QString::number(id));
    ui->nameLable->setText(name);
    ui->addressLable->setText(addr);
    ui->salaryLable->setText(QString::number(salary));
    ui->ageLable->setText(QString::number(age));

}
