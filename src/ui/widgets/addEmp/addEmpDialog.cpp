#include "AddEmpDialog.h"
#include "ui_AddEmpDialog.h"
#include "logger/Log.h"
#include <QMessageBox>
#include "service/model/dtos/EmployeeDto.h"

AddEmpDialog::AddEmpDialog(EmployeeService* employeeService, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEmpDialog)
    , employeeService(employeeService)
{
    ui->setupUi(this);
    connect(ui->okButton, &QPushButton::clicked, this, &AddEmpDialog::onClickOKButton);
}

void AddEmpDialog::onClickOKButton()
{
    qCInfo(logUiWidgetsAddEmp) << "Clicked ok button";
    // check validation
    QString name = ui->nameLineEdit->text().trimmed();
    QString tel = ui->telLineEdit->text().trimmed();
    if (name == "" || tel == "")
        ui->errorLabel->setText("Please fill all inputs.");
    // store info to db
    EmployeeDto newEmp;
    newEmp.name = name; newEmp.tel = tel;
    if (!employeeService->addEmployee(newEmp))
    {
        QMessageBox::critical(this, "Fail to add employee.", employeeService->getError());
    }
    QMessageBox::information(this, "Success", "Employee added successfully.");
    return;
}

AddEmpDialog::~AddEmpDialog()
{
    qCInfo(logUiWidgetsAddEmp) << "AddEmpDialog destroyed";
    delete ui;
}
