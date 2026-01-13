#ifndef CREATETICKETWIDGET_H
#define CREATETICKETWIDGET_H

#include <QWidget>
#include "service/ticketService/TicketService.h"
#include "service/employeeService/EmployeeService.h"
#include "service/employeeScheduleService/EmployeeScheduleService.h"
#include <QListWidgetItem>

namespace Ui {
class CreateTicketWidget;
}

class CreateTicketWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTicketWidget(TicketService* ticketService, EmployeeService* employeeService, EmployeeScheduleService* employeeScheduleService, QWidget *parent = nullptr);
    void setUpEmployeeList();
    void refreshAvailability(QListWidgetItem* item);
    ~CreateTicketWidget();

private:
    Ui::CreateTicketWidget *ui;
    TicketService* ticketService;
    EmployeeService* employeeService;
    EmployeeScheduleService* employeeScheduleService;
};

#endif // CREATETICKETWIDGET_H
