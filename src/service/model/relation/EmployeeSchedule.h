#ifndef EMPLOYEESCHEDULE_H
#define EMPLOYEESCHEDULE_H
struct EmployeeSchedule
{
    int id;
    int empId;
    int ticketId;
    QString appointDate;
    QList<int> timeSlots;
};
#endif // EMPLOYEESCHEDULE_H
