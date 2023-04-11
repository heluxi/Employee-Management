#include "page_register.h"
#include "ui_page_register.h"
#include<QMessageBox>
page_register::page_register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_register),
    ptrsql(nullptr)
{
    ui->setupUi(this);
}

page_register::~page_register()
{
    delete ui;
}

UserInfo page_register::getinfo()
{

    UserInfo info;
    QString username=ui->uerLineEdit->text();
    QString password=ui->passwordLineEdit->text();
    QString confirm=ui->confirmLineEdit->text();
    QString author=ui->authorComboBox->currentText();

    if(confirm==password)
    {
        info.password=ui->passwordLineEdit->text();
        info.uername=ui->uerLineEdit->text();
        info.auth=ui->authorComboBox->currentText();
    }
    else
    {
        info={};
    }

    return info;

}

void page_register::on_registerButton_clicked()
{
    UserInfo info=getinfo();
    if(info.uername.isEmpty())
    {
        QMessageBox::warning(this, tr("危险弹窗"),  tr("警告!!!\n两次输入密码不同！"),
                                        QMessageBox::Ok);
        ui->passwordLineEdit->clear();
        ui->confirmLineEdit->clear();
    }
    else
    {
        ptrsql->AddUser(info);

       this->hide();
       emit sendRegisterSucess();
    }

}

