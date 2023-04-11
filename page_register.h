#ifndef PAGE_REGISTER_H
#define PAGE_REGISTER_H

#include <QWidget>
#include"sql_manage.h"

namespace Ui {
class page_register;
}

class page_register : public QWidget
{
    Q_OBJECT

public:
    explicit page_register(QWidget *parent = nullptr);
    ~page_register();
    UserInfo getinfo();

private slots:
    void on_registerButton_clicked();
signals:
    void sendRegisterSucess();
private:
    Ui::page_register *ui;
    sql_manage *ptrsql;

};

#endif // PAGE_REGISTER_H
