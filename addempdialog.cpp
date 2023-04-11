#include "addempdialog.h"
#include "ui_addempdialog.h"
#include"sql_manage.h"
#include<QMessageBox>

AddempDialog::AddempDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddempDialog)
{
    ui->setupUi(this);
}

AddempDialog::~AddempDialog()
{
    delete ui;
}

void AddempDialog::setType(bool isAdd, EmployInfo info)
{
    this->isAdd=isAdd;
    this->info=info;
    ui->namelineEdit->setText(info.name);
    ui->addressLineEdit->setText(info.address);
    ui->salaryLineEdit->setText(QString::number(info.salary));
    ui->spinBox->setValue(info.age);
    ui->positionLineEdit->setText(info.position);
}



void AddempDialog::on_discardButton_clicked()
{
    this->hide();
}


void AddempDialog::on_saveButton_clicked()
{
    EmployInfo info;
    auto ptr= sql_manage::getinstance();
    if(!(ui->addressLineEdit->text().isEmpty()||ui->namelineEdit->text().isEmpty()||ui->positionLineEdit->text().isEmpty()||ui->positionLineEdit->text().isEmpty()||ui->salaryLineEdit->text().isEmpty()))
   {
        info.name=ui->namelineEdit->text();
        info.age=ui->spinBox->text().toInt();
        info.address=ui->addressLineEdit->text();
        info.position=ui->positionLineEdit->text();
        info.salary=ui->salaryLineEdit->text().toInt();
        info.id=this->info.id;

        if(isAdd)
        {
        ptr->add(info);
        QMessageBox::information(nullptr,tr("Sucess"),tr("添加成功！！"),QMessageBox::Ok);
        this->hide();
        }
        else{

            ptr->Update(info);
            QMessageBox::information(nullptr,tr("Sucess"),tr("修改成功！！"),QMessageBox::Ok);
            this->hide();
        }
    }
    else{


        QMessageBox::warning(this, tr("危险弹窗"),  tr("警告!!!\n输入有空请重新输入！"),
                                                 QMessageBox::Ok);
    }
}

