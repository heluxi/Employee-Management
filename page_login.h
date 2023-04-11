#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include"sql_manage.h"
#include"page_register.h"


namespace Ui {
class Page_Login;
}

class Page_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Page_Login(QWidget *parent = nullptr);
    ~Page_Login();

private slots:
    void on_btn_exit_clicked();

    void on_btn_login_clicked();


    void on_commandLinkButton_clicked();

signals:
    void sendLoginSucess();

private:
    Ui::Page_Login *ui;
    sql_manage *ptrUser;
    page_register reg;

};

#endif // PAGE_LOGIN_H
