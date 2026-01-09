#ifndef CREATETICKETWIDGET_H
#define CREATETICKETWIDGET_H

#include <QWidget>
#include "service/ticket/TicketService.h"

namespace Ui {
class CreateTicketWidget;
}

class CreateTicketWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTicketWidget(TicketService* ticketService, QWidget *parent = nullptr);
    ~CreateTicketWidget();

private:
    Ui::CreateTicketWidget *ui;
    TicketService* ticketService;
};

#endif // CREATETICKETWIDGET_H
