#ifndef TICKETSTABWIDGET_H
#define TICKETSTABWIDGET_H

#include <QWidget>
#include "service/ticketService/TicketService.h"
#include "ui/tickets/createTicket/CreateTicketWidget.h"
#include "service/employeeService/EmployeeService.h"

namespace Ui {
class TicketsTabWidget;
}

class TicketsTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TicketsTabWidget(TicketService* ticketService, EmployeeService* employeeService, EmployeeScheduleService* employeeScheduleService, QWidget *parent = nullptr);
    void displayAllTickets(const QList<Ticket>& tickets );
    void updateTicketStatusById(int newStatus);
    ~TicketsTabWidget();

private:
    Ui::TicketsTabWidget *ui;
    TicketService* ticketService;
    EmployeeService* employeeService;
    EmployeeScheduleService* employeeScheduleService;
    CreateTicketWidget* createTicketWidget;
};

#endif // TICKETSTABWIDGET_H
