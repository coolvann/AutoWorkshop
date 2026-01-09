#include "EmployeeScheduleService.h"

EmployeeScheduleService::EmployeeScheduleService(AutoWorkshopSql* db):m_db(db)
{}

int EmployeeScheduleService::checkEmployeeAvailability(const QString& appointedDate, const QList<int>& timeSlots, const QString& empId)
{
    // TODO: no slot picked, return

    // TODO: emp available

    // TODO: emp unavailable

    // return m_db->checkEmployeeAvailability(appointedDate, timeSlots, empId);
    return -1;
}
