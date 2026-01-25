#ifndef SCHEDULETABWIDGET_H
#define SCHEDULETABWIDGET_H

#include <QWidget>
#include <QDate>
#include <QStackedWidget>
#include "data/AutoWorkshopSql.h"
#include "service/ticketService/TicketService.h"

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
    QStackedWidget* getStack() const; // expose stack in design

private:
    Ui::ScheduleTabWidget *ui;
    TicketService* ticketService;
    QDate currentWeekStart;
};

#endif // SCHEDULETABWIDGET_H
