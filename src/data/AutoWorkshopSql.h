#ifndef AUTOWORKSHOPSQL_H
#define AUTOWORKSHOPSQL_H

#include <QString>
#include <QSqlDatabase>
#include <QDate>
#include "service/model/entity/Ticket.h"
#include "service/model/enums/TicketStatus.h"

class AutoWorkshopSql
{
public:
    AutoWorkshopSql();
    ~AutoWorkshopSql();

    bool openDb(const QString& dbFilePath);
    bool isOpen() const;
    void close();

    bool initSchema();
    bool verifyUser(const QString& username, const QString& password, int* userId = nullptr, QString* role = nullptr);
    bool checkUserExist(const QString& username);
    bool createAccount(const QString& username, const QString& password);
    Ticket getTicket(int ticketId);
    QList<Ticket> filterTicketById(const QString &input);
    QList<Ticket> getWeeklyTickets(const QDate& startDate, const QDate& endDate);
    bool updateTicketStatus(const Ticket& ticket, TicketStatus newStatus);
    QString getLastDbError() const;

private:
    QString connectionName;
    QSqlDatabase db;
    QString lastDbError;

};

#endif // AUTOWORKSHOPSQL_H
