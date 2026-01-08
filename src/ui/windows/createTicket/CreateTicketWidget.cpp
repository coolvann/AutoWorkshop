#include "CreateTicketWidget.h"
#include "ui_CreateTicketWidget.h"

CreateTicketWidget::CreateTicketWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateTicketWidget)
{
    ui->setupUi(this);
}

CreateTicketWidget::~CreateTicketWidget()
{
    delete ui;
}
