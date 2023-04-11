#include "mainwindow.h"
#include"sql_manage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    sql_manage s;
    w.data();
//    w.show();
    return a.exec();
}
