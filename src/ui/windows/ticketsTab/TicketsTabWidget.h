#ifndef TICKETSTABWIDGET_H
#define TICKETSTABWIDGET_H

#include <QWidget>
#include "service/ticket/TicketService.h"
#include "ui/windows/createTicket/CreateTicketWidget.h"

namespace Ui {
class TicketsTabWidget;
}

class TicketsTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TicketsTabWidget(TicketService* ticketService, QWidget *parent = nullptr);
    void displayAllTickets(const QList<Ticket>& tickets );
    void updateTicketStatusById(int newStatus);
    ~TicketsTabWidget();

private:
    Ui::TicketsTabWidget *ui;
    TicketService* ticketService;
    CreateTicketWidget* createTicketWidget;
};

#endif // TICKETSTABWIDGET_H
