#ifndef TICKETSTABWIDGET_H
#define TICKETSTABWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include "service/ticketService/TicketService.h"
#include "ui/tabs/tickets/ticketsHome/TicketsHomePage.h"
#include "ui/tabs/tickets/createTicket/CreateTicketWidget.h"
#include "service/employeeService/EmployeeService.h"
#include "service/employeeScheduleService/EmployeeScheduleService.h"
#include "ui/common/navigation/ILeaveGuard.h"
#include "ui/tabs/baseTab/BaseTab.h"

namespace Ui {
class TicketsTabWidget;
}

class TicketsTabWidget : public BaseTab, public ILeaveGuard
{
    Q_OBJECT

public:
    explicit TicketsTabWidget(TicketService* ticketService, EmployeeService* employeeService, EmployeeScheduleService* employeeScheduleService, QWidget *parent = nullptr);

    ~TicketsTabWidget();
    bool canLeave() override;
    void leaveAndClear() override;

private:
    Ui::TicketsTabWidget *ui;
    TicketService* ticketService;
    EmployeeService* employeeService;
    EmployeeScheduleService* employeeScheduleService;
    TicketsHomePage* ticketsHomePage;
    CreateTicketWidget* createTicketWidget;
};

#endif // TICKETSTABWIDGET_H
