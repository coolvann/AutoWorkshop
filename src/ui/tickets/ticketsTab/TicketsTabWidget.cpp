#include "TicketsTabWidget.h"
#include "ui_TicketsTabWidget.h"
#include "service/ticketService/TimeSlotsProvider.h"
#include <QMessageBox>

TicketsTabWidget::TicketsTabWidget(TicketService* ticketService, EmployeeService* employeeService, EmployeeScheduleService* employeeScheduleService, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TicketsTabWidget)
    , ticketService(ticketService)
    , employeeService(employeeService)
    , employeeScheduleService(employeeScheduleService)
{
    ui->setupUi(this);
    createTicketWidget = new CreateTicketWidget(ticketService, employeeService, employeeScheduleService);
    ui->stackedWidget->addWidget(createTicketWidget);
    // can only select row
    ui->ticketsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    // select only one row
    ui->ticketsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    // cannot edit cell
    ui->ticketsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->ticketsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ticketsTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // get all tickets
    QList<Ticket> tickets = ticketService->getAllTickets();
    displayAllTickets(tickets);
    // show create ticket page
    connect(ui->createTicketButton, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(createTicketWidget);});
}

void TicketsTabWidget::displayAllTickets(const QList<Ticket>& tickets )
{


    // tableWidget_emp in ui for displaying the data:
    ui->ticketsTable->clearContents();
    ui->ticketsTable->setRowCount(tickets.size());

    // set status combobox
    const QStringList texts = {"Created", "In progress", "Done", "Closed"};


    int row = 0;
    foreach (const Ticket &ticket, tickets) {
        QComboBox* combobox = new QComboBox;
        combobox->addItems(texts);
        combobox->setCurrentIndex(ticketStatusToInt(ticket.status));

        ui->ticketsTable->setItem(row, 0, new QTableWidgetItem(QString::number(ticket.id)));
        ui->ticketsTable->setCellWidget(row, 1, combobox);
        ui->ticketsTable->setItem(row, 2, new QTableWidgetItem(ticket.resgisId));
        ui->ticketsTable->setItem(row, 3, new QTableWidgetItem(ticket.customer));
        ui->ticketsTable->setItem(row, 4, new QTableWidgetItem(ticket.date));

        // manually change ticket status, update database
        connect(combobox, &QComboBox::currentIndexChanged, this, &TicketsTabWidget::updateTicketStatusById);

        QStringList timeStr;
        for(int i =0; i <5; ++i)
        {
            if (ticket.timeSlots[i] == 1)
                timeStr.append(TimeSlotProvider::timeSlots().at(i).start.toString("hh:mm") + " - " + TimeSlotProvider::timeSlots().at(i).end.toString("hh:mm"));
        }
        QString timeString = timeStr.join(" ");

        ui->ticketsTable->setItem(row, 5, new QTableWidgetItem(timeString));

        ui->ticketsTable->setItem(row, 6, new QTableWidgetItem(ticket.empNames.join(", ")));
        row++;
    }
}

// update ticket status when user changes it
void TicketsTabWidget::updateTicketStatusById(int newStatus)
{
    int row = ui->ticketsTable->currentRow();
    int ticketId = ui->ticketsTable->item(row, 0)->text().toInt();
    qDebug()<<"TicketsTabWidget::updateTicketStatus id: " << ticketId << " to status: " << newStatus;

    bool res = ticketService->updateTicketStatusById(ticketId, newStatus);
    if (res)
        QMessageBox::information(nullptr, "Info", "Status changed!");
    else
        QMessageBox::information(nullptr, "Info", "Fail to change status!");

}

TicketsTabWidget::~TicketsTabWidget()
{
    delete ui;
}
