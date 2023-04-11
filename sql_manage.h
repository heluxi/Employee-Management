#ifndef SQL_MANAGE_H
#define SQL_MANAGE_H

#include <QObject>
#include<QSqlDatabase>

struct EmployInfo
{
    int id;
    QString name;
    int age;
    QString address;
    QString position;
    int salary;


};

struct UserInfo
{
   QString uername;
   QString password;
   QString auth;
};

class sql_manage : public QObject
{
    Q_OBJECT
public:

    static sql_manage *ptrsql;
    static sql_manage *getinstance()
    {
        if(ptrsql==nullptr)
        {
            ptrsql= new sql_manage;
        }
        return ptrsql;
    }

    void init();
    explicit sql_manage(QObject *parent = nullptr);
    quint32 getCount();
    QList<EmployInfo> getPage(quint32 page,quint32 uiCnt);
    bool add(EmployInfo);
    bool delEmp(int id);
    void clearStuTable();
    void Update(EmployInfo);
    QList<EmployInfo> select(QString name);

    QList<UserInfo> getAllUser();
    bool isExit(QString strUser);
    bool UpdateUser(UserInfo info);
    bool AddUser(UserInfo info);
    bool delUser(QString strUserName);
    UserInfo selUser(QString name);

private:
    QSqlDatabase db;
signals:


};

#endif // SQL_MANAGE_H
