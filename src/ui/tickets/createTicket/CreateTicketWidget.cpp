#include "CreateTicketWidget.h"
#include "ui_CreateTicketWidget.h"
#include "domain/employee/Employee.h"
#include "logger/Log.h"
#include <QMessageBox>

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

void CreateTicketWidget::refreshAvailability(QListWidgetItem* item)
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
        EmpAvailability availability = employeeScheduleService->checkEmployeeAvailability(empId, appointedDate, timeSlots);
        switch (availability)
        {
        case EmpAvailability::NoSlotSelected:
            QMessageBox::information(this, "Tip", "Please check at least 1 slot!");
            ui->employeeListWidget->blockSignals(true);
            item->setCheckState(Qt::Unchecked);
            ui->employeeListWidget->blockSignals(false);
            break;
        case EmpAvailability::Available:
            break;
        case EmpAvailability::NotAvailable:
            QMessageBox::information(this, "Info", "Staff not available!");
            ui->employeeListWidget->blockSignals(true);
            item->setCheckState(Qt::Unchecked);
            ui->employeeListWidget->blockSignals(false);
            break;
        }
    }
}

bool CreateTicketWidget::hasUnsavedChanges()
{
    if (!ui->brandInput->text().isEmpty() || ui->checkBox1->isChecked() || ui->checkBox2->isChecked() || ui->checkBox3->isChecked() ||
        ui->checkBox4->isChecked() || ui->checkBox5->isChecked() || !ui->customerInput->text().isEmpty() || !ui->descriptionInput->toPlainText().isEmpty()
        || !ui->modelInput->text().isEmpty() || !ui->regisIdInput->text().isEmpty())
    {
        return true;
    }
    return false;
}

void CreateTicketWidget::clearForm()
{
    ui->customerInput->clear();
    ui->brandInput->clear();
    ui->modelInput->clear();
    ui->regisIdInput->clear();

    ui->dateInput->clear();

    ui->checkBox1->setChecked(false);
    ui->checkBox2->setChecked(false);
    ui->checkBox3->setChecked(false);
    ui->checkBox4->setChecked(false);
    ui->checkBox5->setChecked(false);

    ui->employeeListWidget->clearSelection();
    for (int i = 0; i < ui->employeeListWidget->count(); ++i) {
        auto* item = ui->employeeListWidget->item(i);
        item->setCheckState(Qt::Unchecked);
    }
}

CreateTicketWidget::~CreateTicketWidget()
{
    delete ui;
}
