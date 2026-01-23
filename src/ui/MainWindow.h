#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include "ui/schedule/scheduleTab/ScheduleTabWidget.h"
#include "ui/tickets/ticketsTab/TicketsTabWidget.h"
#include "ui/employees/employeeTab/EmployeeTabWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadAllTabs();
    void setFirstTabPage();
    void onClickOtherTab(int index);
    bool eventFilter(QObject *watched, QEvent *event);

private slots:


private:
    Ui::MainWindow *ui;
    ScheduleTabWidget* scheduleTab;
    TicketsTabWidget* ticketsTab;
    EmployeeTabWidget* employeeTab;
};
#endif // MAINWINDOW_H
