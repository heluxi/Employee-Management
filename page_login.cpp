#include "page_login.h"
#include "ui_page_login.h"
#include<QSqlQuery>
#include<QMessageBox>



Page_Login::Page_Login(QWidget *parent) :
    QWidget(parent),
    ptrUser(nullptr),
    ui(new Ui::Page_Login)

{
    ui->setupUi(this);

}

Page_Login::~Page_Login()
{
    delete ui;
}

void Page_Login::on_btn_exit_clicked()
{
    exit(0);
}


void Page_Login::on_btn_login_clicked()
{
    //数据库查找用户名和密码
    QString username=ui->_user->text();
    QString password=ui->password->text();
    UserInfo info= ptrUser->selUser(username);



    //失败就提示 成功进入主界面
        if(info.uername==username&&info.password==password)
        {

            QMessageBox::information(this, tr("Sucess!"),  tr("登陆成功！"),
                                                     QMessageBox::Ok);
            this->hide();
            emit sendLoginSucess();
        }
        else
        {
            QMessageBox::warning(this, tr("危险弹窗"),  tr("警告!!!\n密码或用户名错误！\n请重新输入！"),
                                                     QMessageBox::Ok);
            ui->_user->clear();
            ui->password->clear();
        }


}





void Page_Login::on_commandLinkButton_clicked()
{
    reg.show();
    this->hide();


    auto f= [&](){
        this->show();
    };

    connect(&reg,&page_register::sendRegisterSucess,this,f);

}

