#ifndef ADDEMPDIALOG_H
#define ADDEMPDIALOG_H

#include <QDialog>
#include"sql_manage.h"

namespace Ui {
class AddempDialog;
}

class AddempDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddempDialog(QWidget *parent = nullptr);
    ~AddempDialog();

    void setType(bool isAdd,EmployInfo info={});

private slots:


    void on_discardButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::AddempDialog *ui;
    bool isAdd;
    EmployInfo info;
};

#endif // ADDEMPDIALOG_H
