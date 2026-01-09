#include "CreateTicketWidget.h"
#include "ui_CreateTicketWidget.h"
#include "service/model/entity/Employee.h"
#include "logger/Log.h"

CreateTicketWidget::CreateTicketWidget(TicketService* ticketService, EmployeeService* employeeService, EmployeeScheduleService* employeeScheduleService, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateTicketWidget)
    , ticketService(ticketService)
    , employeeService(employeeService)
    , employeeScheduleService(employeeScheduleService)
{
    ui->setupUi(this);
    ui->dateInput->setDate(QDate::currentDate());
    setUpEmployeeList();
    // when employee checked, obtain availability
    connect(ui->employeeListWidget, &QListWidget::itemChanged, this, &CreateTicketWidget::refreshAvailability);
}


void CreateTicketWidget::setUpEmployeeList()
{
    QList<Employee> emps = employeeService->getAllEmployees();
    qCInfo(logUi) << "Getting all employees success!";
    foreach (const Employee& emp, emps) {
        QListWidgetItem* listItem = new QListWidgetItem(emp.name, ui->employeeListWidget);
        listItem->setFlags(listItem->flags() | Qt::ItemIsUserCheckable);
        listItem->setCheckState(Qt::Unchecked);
        listItem->setData(Qt::UserRole, emp.id);
    }
}

void CreateTicketWidget::refreshAvailability(const QListWidgetItem* item)
{
    if(item->checkState() == Qt::Checked) {
        // Handle the checked state
        qCInfo(logUi) << item->text() << " is checked.";
        // query if emp is available
        QString appointedDate = ui->dateInput->text();   // yyyy-mm-dd
        qCInfo(logUi) << "Date input: " << appointedDate;
        QList<int> timeSlots;
        timeSlots.append(ui->checkBox1->isChecked() ? 1: 0);
        timeSlots.append(ui->checkBox2->isChecked() ? 1: 0);
        timeSlots.append(ui->checkBox3->isChecked() ? 1: 0);
        timeSlots.append(ui->checkBox4->isChecked() ? 1: 0);
        timeSlots.append(ui->checkBox5->isChecked() ? 1: 0);
        qCInfo(logUi) << "Check boxes states: " << timeSlots;
        QString empId = item->data(Qt::UserRole).toString();
        qCInfo(logUi) << "Selected employee id: " << empId;
        int res = employeeScheduleService->checkEmployeeAvailability(appointedDate, timeSlots, empId);
        // if (res == -1)
        //     QMessageBox::information(nullptr, "Info", "Please choose slot first!");
        // else if(res > 0)
        // {
        //     QMessageBox::information(nullptr, "Info", "Employee not available!");
        //     item->setCheckState(Qt::Unchecked);
        // }
    }
}

CreateTicketWidget::~CreateTicketWidget()
{
    delete ui;
}
