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
    // only single row can be selected
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    refreshEmployeeTable();

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
        refreshEmployeeTable();
    } else
    {
        addEmpDialog.close();
    }
}

void EmployeeTabWidget::refreshEmployeeTable()
{
    QList<Employee> employees = employeeService->getAllEmployees();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(employees.size());
    // do not show number on left table side
    ui->tableWidget->verticalHeader()->setVisible(false);
    int row = 0;
    foreach (const Employee& emp, employees) {
        auto index = new QTableWidgetItem(QString::number(row+1));
        auto name = new QTableWidgetItem(emp.name);
        auto tel = new QTableWidgetItem(emp.tel);
        auto createTime = new QTableWidgetItem(emp.createTime);
        for (auto item : {name, tel, createTime})
        {
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        ui->tableWidget->setItem(row, 0, index);
        ui->tableWidget->setItem(row, 1, name);
        ui->tableWidget->setItem(row, 2, tel);
        ui->tableWidget->setItem(row, 3, createTime);
        row++;
    }
}

EmployeeTabWidget::~EmployeeTabWidget()
{
    delete ui;
}
