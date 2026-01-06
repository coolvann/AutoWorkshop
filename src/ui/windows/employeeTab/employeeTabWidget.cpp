#include "EmployeeTabWidget.h"
#include "ui_EmployeeTabWidget.h"
#include "ui/widgets/addEmp/AddEmpDialog.h"
#include "logger/Log.h"
#include <QDialog>

EmployeeTabWidget::EmployeeTabWidget(EmployeeService* employeeService, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmployeeTabWidget)
    , employeeService(employeeService)
{
    ui->setupUi(this);

    // click add button show add emp dialog
    connect(ui->addEmpButton, &QPushButton::clicked, this, &EmployeeTabWidget::onClickAddButton);

}

void EmployeeTabWidget::onClickAddButton()
{
    qCInfo(logUiWidgetsAddEmp) << "Clicked add button";
    AddEmpDialog addEmpDialog(employeeService, this);
    if (addEmpDialog.exec() == QDialog::Accepted)
    {
        addEmpDialog.close();
        // TODO: refresh the emp table
    } else
    {
        addEmpDialog.close();
    }
}

EmployeeTabWidget::~EmployeeTabWidget()
{
    delete ui;
}
