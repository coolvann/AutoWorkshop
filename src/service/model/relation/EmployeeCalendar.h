#ifndef EMPLOYEECALENDAR_H
#define EMPLOYEECALENDAR_H
struct EmployeeCalendar
{
    int emId;
    QString name;
    int ticketId;
    QString customer;
    QString appDate;
    QList<int> timeSlots;
};
#endif // EMPLOYEECALENDAR_H
