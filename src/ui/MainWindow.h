#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include "ui/tabs/schedule/scheduleTab/ScheduleTabWidget.h"
#include "ui/tabs/tickets/ticketsTab/TicketsTabWidget.h"
#include "ui/tabs/employees/employeeTab/EmployeeTabWidget.h"
#include "ui/common/navigation/tabNavigationController/tabnavigationcontroller.h"
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
    bool eventFilter(QObject *watched, QEvent *event);

private slots:


private:
    Ui::MainWindow *ui;
    ScheduleTabWidget* scheduleTab;
    TicketsTabWidget* ticketsTab;
    EmployeeTabWidget* employeeTab;
    TabNavigationController* tabNavigationController;
};
#endif // MAINWINDOW_H
