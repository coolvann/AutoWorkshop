#include "EmployeeService.h"

EmployeeService::EmployeeService(AutoWorkshopSql* db):m_db(db)
{

}

bool EmployeeService::addEmployee(const EmployeeDto& newEmp)
{
    if (!m_db->addEmployee(newEmp))
    {
        setError(m_db->getLastDbError());
        return false;
    }
    return true;
}

void EmployeeService::setError(QString err)
{
    error = err;
}

QList<Employee> EmployeeService::getAllEmployees()
{
    return m_db->getAllEmployees();
}

QList<Employee> EmployeeService::filterByName(const QString& name)
{
    return m_db->filterByName(name);
}

QString EmployeeService::getError()
{
    return error;
}
