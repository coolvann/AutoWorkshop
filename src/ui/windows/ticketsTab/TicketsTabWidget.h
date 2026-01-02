#ifndef TICKETSTABWIDGET_H
#define TICKETSTABWIDGET_H

#include <QWidget>
#include "service/ticket/TicketService.h"

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
};

#endif // TICKETSTABWIDGET_H
