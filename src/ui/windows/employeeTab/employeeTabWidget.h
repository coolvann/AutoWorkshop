#ifndef EMPLOYEETABWIDGET_H
#define EMPLOYEETABWIDGET_H

#include <QWidget>
#include "service/employee/EmployeeService.h"


namespace Ui {
class EmployeeTabWidget;
}

class EmployeeTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeTabWidget(EmployeeService* employeeService, QWidget *parent = nullptr);
    void refreshEmployeeTable();
    ~EmployeeTabWidget();
    void onClickAddButton();

private:
    Ui::EmployeeTabWidget *ui;
    EmployeeService* employeeService;
};

#endif // EMPLOYEETABWIDGET_H
