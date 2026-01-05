#ifndef ADDEMPDIALOG_H
#define ADDEMPDIALOG_H

#include <QDialog>
#include "service/employee/EmployeeService.h"

namespace Ui {
class AddEmpDialog;
}

class AddEmpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmpDialog(EmployeeService* employeeService, QWidget *parent = nullptr);
    ~AddEmpDialog();
    void onClickOKButton();

private:
    Ui::AddEmpDialog *ui;
    EmployeeService* employeeService;
};

#endif // ADDEMPDIALOG_H
