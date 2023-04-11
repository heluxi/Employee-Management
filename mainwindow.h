#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
#include"page_login.h"
#include"itemform.h"
#include<QListWidgetItem>
#include<QMessageBox>
#include<QFile>
#include<QKeyEvent>
#include"sql_manage.h"
#include"addempdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void data();


private slots:


    void on_deleteButton_clicked();

    void on_updateButton_clicked();

    void on_addButton_clicked();

    void on_exitButton_clicked();

    void showList();

    void on_searchButton_clicked();





    void on_showButton_clicked();

private:
    Ui::MainWindow *ui;
    sql_manage *ptrEmp;
    Page_Login login;
    AddempDialog addDlg;

};
#endif // MAINWINDOW_H
