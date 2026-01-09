#include "CreateTicketWidget.h"
#include "ui_CreateTicketWidget.h"

CreateTicketWidget::CreateTicketWidget(TicketService* ticketService, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateTicketWidget)
    , ticketService(ticketService)
{
    ui->setupUi(this);
}

CreateTicketWidget::~CreateTicketWidget()
{
    delete ui;
}
