#ifndef EMPLOYEESCHEDULESERVICE_H
#define EMPLOYEESCHEDULESERVICE_H
#include "data/AutoWorkshopSql.h"

class EmployeeScheduleService
{
public:
    EmployeeScheduleService(AutoWorkshopSql* db);
    int checkEmployeeAvailability(const QString& appointedDate, const QList<int>& timeSlots, const QString& empId);

private:
    AutoWorkshopSql* m_db;
    QString error;
};

#endif // EMPLOYEESCHEDULESERVICE_H
