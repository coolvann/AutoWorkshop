#include "EmployeeScheduleService.h"
#include "src/logger/Log.h"

EmployeeScheduleService::EmployeeScheduleService(AutoWorkshopSql* db):m_db(db)
{
    Q_ASSERT(m_db != nullptr);
}

EmpAvailability EmployeeScheduleService::checkEmployeeAvailability(const QString& empId, const QString& appointedDate, const QList<int>& timeSlots)
{
    qCInfo(logEmployeeSchedule) << "Check employee availability.";
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
    {
        qCInfo(logEmployeeSchedule) << "No time slot selected.";
        return EmpAvailability::NoSlotSelected;
    }
    qCInfo(logEmployeeSchedule) << "Slots selected. Check employee availability.";
     qDebug() << "DB pointer:" << m_db;
    // TODO: emp available
    int conflicts = m_db->countScheduleConflicts(empId, appointedDate, timeSlots);
    if (conflicts > 0)
    {
        qCInfo(logEmployeeSchedule) << "Employee not available.";
        return EmpAvailability::NotAvailable;
    }

    // TODO: emp unavailable
    qCInfo(logEmployeeSchedule) << "Employee available.";
    return EmpAvailability::Available;

}
