#ifndef EMPLOYEESERVICE_H
#define EMPLOYEESERVICE_H
#include "data/AutoWorkshopSql.h"
#include "service/model/dtos/EmployeeDto.h"
#include "service/model/entity/Employee.h"

class EmployeeService
{
public:
    EmployeeService(AutoWorkshopSql* db);
    bool addEmployee(const EmployeeDto& newEmp);
    QList<Employee> getAllEmployees();
    QList<Employee> filterByName(const QString& name);
    void setError(QString err);
    QString getError();

private:
    AutoWorkshopSql* m_db;
    QString error;
};

#endif // EMPLOYEESERVICE_H
