#ifndef SCHEDULETABWIDGET_H
#define SCHEDULETABWIDGET_H

#include <QWidget>
#include <QDate>
#include "data/AutoWorkshopSql.h"
#include "service/ticket/TicketService.h"

namespace Ui {
class ScheduleTabWidget;
}

class ScheduleTabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleTabWidget(TicketService* ticketService, QWidget *parent = nullptr);
    ~ScheduleTabWidget();
    void loadWeek(const QDate &startDate);
    QDate getCurrentWeekStart(const QDate &date);
    void onPressNextWeekButton();
    void onPressPreviousWeekButton();
    updateTicketStatus();

private:
    Ui::ScheduleTabWidget *ui;
    TicketService* ticketService;
    QDate currentWeekStart;
};

#endif // SCHEDULETABWIDGET_H
