#include "ScheduleTabWidget.h"
#include "ui_ScheduleTabWidget.h"
#include "app/AppContext.h"
#include "service/model/entity/Ticket.h"
#include "ui/widgets/SlotWidget.h"

ScheduleTabWidget::ScheduleTabWidget(TicketService* ticketService, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleTabWidget)
    ,ticketService(ticketService)
{
    ui->setupUi(this);
    // headers stretch
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->scheduleTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // cannot edit cell
    ui->scheduleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // enable  to accept drop and event filte
    ui->scheduleTable->viewport()->installEventFilter(this);
    ui->scheduleTable->viewport()->setAcceptDrops(true);
    ui->scheduleTable->setDragEnabled(true);
    ui->scheduleTable->setAcceptDrops(true);
    ui->scheduleTable->setDropIndicatorShown(true);
    ui->scheduleTable->setDragDropMode(QAbstractItemView::InternalMove);
    ui->scheduleTable->setDragDropOverwriteMode(false);

    currentWeekStart = getCurrentWeekStart(QDate::currentDate());
    loadWeek(currentWeekStart);
}

/**
 * @brief ScheduleTabWidget::loadWeek
 * @param currentWeekStart
 */
void ScheduleTabWidget::loadWeek(const QDate& currentWeekStart)
{
    QDate currentWeekEnd = currentWeekStart.addDays(4);
    ui->weekLabel->setText(QString("%1 - %2")
                               .arg(currentWeekStart.toString("MMM dd"))
                               .arg(currentWeekEnd.toString("MMM dd, yyyy")));
    ui->scheduleTable->clearContents();

    QList<Ticket> tickets = ticketService->getWeeklyTickets(currentWeekStart, currentWeekEnd);

    //put ticket widget on table cell
    foreach (const Ticket& ticket, tickets) {

        // Convert date and time to row and column indices
        qDebug()<<"date: " << ticket.date;
        QDate date = QDate::fromString(ticket.date, "yyyy-MM-dd");
        int col = date.dayOfWeek()-1; // monday 1
        qDebug()<<"day of week" <<col;

        Ticket updatedTicket = ticketService->refreshStatus(ticket);
        for (int i = 0; i < 5; ++i)
        {
            if (updatedTicket.timeSlots[i] == 1)
            {
                int row = i;
                SlotWidget* slotInfo = new SlotWidget();
                // make slot widget
                slotInfo->setTicketInfo(updatedTicket);
                // check if there already has a ticket widget
                QWidget* existingWidget = ui->scheduleTable->cellWidget(row*2, col);
                qDebug()<<"set ticket slot widget";
                if (existingWidget)
                    // put to next
                    ui->scheduleTable->setCellWidget(row*2+1, col, slotInfo);
                else
                {   // put
                    ui->scheduleTable->setCellWidget(row*2, col, slotInfo);

                }

            }
        }
    }

    // distribute space evenly
    ui->scheduleTable->resizeColumnsToContents();
    ui->scheduleTable->resizeRowsToContents();
    ui->scheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->scheduleTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

/**
 * @brief ScheduleTabWidget::getCurrentWeekStart
 * @param date
 * @return QDate date of monday
 */
QDate ScheduleTabWidget::getCurrentWeekStart(const QDate &date)
{
    int dayOfWeek = date.dayOfWeek();
    QDate startOfWeek = date.addDays(-((dayOfWeek + 6) % 7));
    return startOfWeek;
}

ScheduleTabWidget::~ScheduleTabWidget()
{
    delete ui;
}
