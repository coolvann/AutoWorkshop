#include "EmployeeScheduleService.h"


EmployeeScheduleService::EmployeeScheduleService(AutoWorkshopSql* db):m_db(db)
{}

EmpAvailability EmployeeScheduleService::checkEmployeeAvailability(const QString& empId, const QString& appointedDate, const QList<int>& timeSlots)
{
    // TODO: no slot picked, return
    bool slotsPicked = false;
    for (int timeSlot : timeSlots)
    {
        if (timeSlot == 1)
        {
            slotsPicked = true;
            break;
        }
    }
    if (!slotsPicked)
        return EmpAvailability::NoSlotSelected;
    // TODO: emp available
    int conflicts = m_db->countScheduleConflicts(empId, appointedDate, timeSlots);
    if (conflicts > 0)
        return EmpAvailability::NotAvailable;
    // TODO: emp unavailable
    return EmpAvailability::Available;

}
