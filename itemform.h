#ifndef ITEMFORM_H
#define ITEMFORM_H

#include <QMainWindow>

namespace Ui {
class itemForm;
}

class itemForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit itemForm(QWidget *parent = nullptr);
    ~itemForm();
    void setStaffInfo(int id,int age,QString name,QString addr,int salary);

private:
    Ui::itemForm *ui;

};

#endif // ITEMFORM_H


