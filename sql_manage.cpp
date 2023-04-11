#include "sql_manage.h"
#include <QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>

sql_manage * sql_manage::ptrsql=nullptr;

void sql_manage::init()
{
    if(QSqlDatabase::drivers().isEmpty())
        qDebug()<<"NO database drivers found";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("compary.db");
    if(!db.open())
    {
        qDebug()<<"Database open failed!"<<db.lastError();
    }
}

sql_manage::sql_manage(QObject *parent)
    : QObject{parent}
{
//    //创建数据库
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("compary.db");
//    if(!db.open())
//    {
//        qDebug()<<"Database open failed!"<<db.lastError();
//    }
#if 0
    QSqlQuery query;
    QString sqlCreateTable= QString("create table staff(id integer primary key autoincrement,"
                                    " name varchar(20),"
                                    " age  int,"
                                    " address varchar(50),"
                                    " position varchar(50),"
                                    " salary int);"
                                    );
    if(!query.exec(sqlCreateTable))
    {
        qDebug()<<"create table error!"<<db.lastError();
    }

    QString sqlInsert =QString("insert into staff(name,age,address,position,salary) "
                               "values('张三',20,'No1234 street','项目经理',12000);"

                               );
    if(!query.exec(sqlInsert))
    {
        qDebug()<<"insert into  error!"<<db.lastError();//
    }
    sqlCreateTable= QString("create table user(username text,"
                                    "password text,"
                                    "author text);"

                                    );
    if(!query.exec(sqlCreateTable))
    {
        qDebug()<<"create table error!"<<db.lastError();
    }
    sqlInsert =QString("insert into user(username,password,author)"
                       "values('hlx','12345','管理员');"

                       );
    if(!query.exec(sqlInsert))
    {
        qDebug()<<"insert user error";
    }
#endif
 }

quint32 sql_manage::getCount()
{
    QSqlQuery query;

    if(!query.exec("select count(id) from staff"))
    {
        qDebug()<<"select  all staff error!"<<db.lastError();
    }
    quint32 uicnt;
    while(query.next())
    {
        uicnt=query.value(0).toInt();
    }
//    qDebug()<<uicnt;
    return uicnt;

}

QList<EmployInfo> sql_manage::getPage(quint32 page, quint32 uiCnt)
{
    QList<EmployInfo> l;
    QSqlQuery query(db);


    QString selectsql=QString ("select * from staff order by id limit %1 offset %2").arg(uiCnt).arg(page*uiCnt);
    if(!query.exec(selectsql))
    {
        qDebug()<<"select error"<<db.lastError();
    }

    EmployInfo info;
    while(query.next())
    {

        info.id=query.value(0).toInt();
        info.name=query.value(1).toString();
        info.age=query.value(2).toInt();
        info.address=query.value(3).toString();
        info.position=query.value(4).toString();
        info.salary=query.value(5).toInt();
//        qDebug()<<info.address;
        l.push_back(info);
    }

    return l;
}

bool sql_manage::add(EmployInfo info)
{
    QSqlQuery query;
    //String sqlInsert=QString ("insert into staff(name,age,address,salary)"
    //                                "values('%1',%2,'%3',%4);").arg(name).arg(age.toInt()).arg(address).arg(salary.toInt());
//    qDebug()<<info.address;
    QString sqlInsert=QString ("insert into staff(name,age,position,address,salary)"
                                    "values('%1',%2,'%3','%4',%5);").arg(info.name).arg(info.age).arg(info.position).arg(info.address).arg(info.salary);
    if(!query.exec(sqlInsert))
    {
        qDebug()<<"Insert Error!"<<db.lastError();
        return false;
    }
    return true;
}

bool sql_manage::delEmp(int id)
{
    QSqlQuery query;
//    qDebug()<<id;
    QString deletesql=QString("delete from staff where id = %1").arg(id);

    if(!query.exec(deletesql))
    {
        qDebug()<<"delete error!!!"<<db.lastError();
        return false;
    }

    return true;


}

void sql_manage::clearStuTable()
{
    QSqlQuery query;
    QString deletesql=QString("delete from sqlite_sequence where name ='student'");

    if(!query.exec(deletesql))
    {
        qDebug()<<"delete error!"<<db.lastError();

    }



}

void sql_manage::Update(EmployInfo info)
{
    QSqlQuery query;

    QString sqlUpdate=QString ("update staff set name='%1',age=%2 ,position='%3',address='%4', salary=%5 where id =%6;").arg(info.name).arg(info.age).arg(info.position).arg(info.address).arg(info.salary).arg(info.id);
    if(!query.exec(sqlUpdate))
    {
        qDebug()<<"Update Error!"<<db.lastError();

    }
}

QList<EmployInfo>  sql_manage::select(QString name)
{
    QSqlQuery query;
    QString selectsql=QString("select *from staff where name= '%1'").arg(name);
    if(!query.exec(selectsql))
    {
        qDebug()<<"Select Error!"<<db.lastError();

    }
    QList<EmployInfo> l;

    while(query.next())
    {
        EmployInfo info;
        info.id=query.value(0).toInt();
        info.name=query.value(1).toString();
        info.age=query.value(2).toInt();
        info.address=query.value(3).toString();
        info.position=query.value(4).toString();
        info.salary=query.value(5).toInt();
        l.append(info);
    }
    return  l;
}

QList<UserInfo> sql_manage::getAllUser()
{
    QList<UserInfo> l;
    QSqlQuery query;
    QString selectsql=QString ("select * from user");
    if(!query.exec(selectsql))
    {
        qDebug()<<"select error"<<db.lastError();
    }
    UserInfo info;
    while(query.next())
    {
        info.uername=query.value(0).toString();
        info.password=query.value(1).toString();
        info.auth=query.value(2).toString();
        l.push_back(info);
    }
    return l;
}

bool sql_manage::isExit(QString strUser)
{
    QSqlQuery query;
    QString str=QString ("select *from user where username='%1';").arg(strUser);
    if(!query.exec(str))
    {
        qDebug()<<"select from user error"<<db.lastError();
        return false;
    }
    return true;

}

bool sql_manage::UpdateUser(UserInfo info)
{
    QSqlQuery query;
    QString sqlUpdate=QString ("update user set password='%1' ,author='%2' where username='%3';").arg(info.password).arg(info.auth).arg(info.uername);
    if(!query.exec(sqlUpdate))
    {
        qDebug()<<"Update Error!"<<db.lastError();
        return false;
    }
    return true;
}




bool sql_manage::AddUser(UserInfo info)
{

    QSqlQuery query;
    QString sqlInsert=QString ("insert into user(username,password,author)"
                                    "values('%1','%2','%3');").arg(info.uername).arg(info.password).arg(info.auth);
    if(!query.exec(sqlInsert))
    {
        qDebug()<<"Insert Error!"<<db.lastError();
        return false;
    }
    return true;
}

bool sql_manage::delUser(QString strUserName)
{
    QSqlQuery query;
    QString deletesql=QString("delete from user where username='%1'").arg(strUserName);
    if(!query.exec(deletesql))
    {
        qDebug()<<"delete from user error"<<db.lastError();
        return false;
    }
    return true;
}

UserInfo sql_manage::selUser(QString name)
{

    UserInfo info;
    QSqlQuery query;
    QString selectsql=QString("select * from user where username='%1'").arg(name);

    if(!query.exec(selectsql))
    {

        qDebug()<<"select error";

    }

    else
    {
        query.next();
        info.uername=query.value(0).toString();
        info.password=query.value(1).toString();
        info.auth=query.value(2).toString();

    }
    return info;
}
