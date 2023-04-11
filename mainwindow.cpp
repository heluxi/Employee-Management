#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QRandomGenerator>
#include<QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,ptrEmp(nullptr)
{
    ui->setupUi(this);
    login.show();
    auto f= [&](){
        this->show();
    };

    connect(&login,&Page_Login::sendLoginSucess,this,f);

    QTreeWidgetItem *par=new QTreeWidgetItem(ui->treeWidget,QStringList("Employee Management"));
    ui->treeWidget->addTopLevelItem(par);

    QTreeWidgetItem *c1=new QTreeWidgetItem(par,QStringList("员工管理"));
    QTreeWidgetItem *c2=new QTreeWidgetItem(par,QStringList("管理员管理"));

    par->addChild(c1);
    par->addChild(c2);

    ui->treeWidget->expandAll();

    ui->stackedWidget->setCurrentIndex(0);



    ptrEmp=sql_manage::getinstance();
    ptrEmp->init();

    showList();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::data()
{


    QRandomGenerator r;
    r.seed(0);


    for(int i=0;i<100;i++)
    {
        int add=r.bounded(0,9);
        EmployInfo info;

        info.address=QString("Avenue %1").arg(add);
        int sal=r.bounded(2000,20000);
        info.salary=sal;
        int t=r.bounded(1,4);


        switch (t) {
        case 1:
            info.age=23;
            info.position="软件工程师";
            info.name=QString("张%1").arg(add);
            break;
        case 2:
            info.age=30;
            info.position="项目经理";
            info.name=QString("李%1").arg(add);
            break;
        case 3:

            info.age=24;
            info.position="测试";
            info.name=QString("王%1").arg(add);
            break;

        default:
            break;
        }



        ptrEmp->add(info);

    }
}




void MainWindow::on_deleteButton_clicked()
{
    int i=ui->tableWidget->currentRow();
    if(i>=0)
    {
       int  id =ui->tableWidget->item(i,1)->text().toInt();
//       qDebug()<<id;
       ptrEmp->delEmp(id);
       showList();
       QMessageBox::information(this,tr("Sucess"),tr("删除成功！！"),QMessageBox::Ok);

    }
    else
    {
        QMessageBox::warning(this, tr("危险弹窗"),  tr("警告!!!\n删除失败！"),
                                        QMessageBox::Ok);
    }

}


void MainWindow::on_updateButton_clicked()
{

    EmployInfo info;
    int i=ui->tableWidget->currentRow();
    if(i>=0)
    {
    info.id =ui->tableWidget->item(i,1)->text().toInt();
    info.name =ui->tableWidget->item(i,2)->text();
    info.age =ui->tableWidget->item(i,3)->text().toInt();
    info.address=ui->tableWidget->item(i,4)->text();
    info.position=ui->tableWidget->item(i,5)->text();
    info.salary=ui->tableWidget->item(i,6)->text().toInt();
    addDlg.setType(false,info);
    addDlg.exec();


    }

    showList();



}


void MainWindow::on_addButton_clicked()
{
    addDlg.setType(true);
    addDlg.exec();
    showList();
}


void MainWindow::on_exitButton_clicked()
{
    exit(0);
}

void MainWindow::showList()
{

    auto cnt=ptrEmp->getCount();
    QList<EmployInfo> employ=ptrEmp->getPage(0,cnt);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableWidget->setRowCount(cnt);

    for(int i=0;i<employ.size();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(employ[i].id)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(employ[i].name));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(employ[i].age)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(employ[i].address));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(employ[i].position));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(employ[i].salary)));
    }

}


void MainWindow::on_searchButton_clicked()
{

    QString str=ui->searchlineEdit->text();
    QList<EmployInfo> employlist=ptrEmp->select(str);
    if(employlist.isEmpty())
    {
        QMessageBox::warning(this, tr("危险弹窗"),  tr("警告!!!\n输入名字有误！\n请重新输入！"),
                                                 QMessageBox::Ok);
    }
    else{


        int cnt=0;
        ui->tableWidget->clear();
        for(int i=0;i<employlist.size();i++)
        {
            cnt++;
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(employlist[i].id)));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(employlist[i].name));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(employlist[i].age)));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(employlist[i].address));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(employlist[i].position));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(employlist[i].salary)));
        }
        ui->tableWidget->setRowCount(cnt);
    }
    ui->searchlineEdit->clear();
}







void MainWindow::on_showButton_clicked()
{
    showList();
}

