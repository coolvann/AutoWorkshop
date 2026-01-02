#include "AutoWorkshopSql.h"
#include <QStandardPaths>
#include <QDir>
#include <QUuid>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "service/model/enums/TicketStatus.h"

AutoWorkshopSql::AutoWorkshopSql()
{
    QString connectionName = "autoworkshop_vann";
    if (QSqlDatabase::contains(connectionName))
        db = QSqlDatabase::database(connectionName);
    else
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);

}

bool AutoWorkshopSql::openDb()
{
    if (db.isOpen())
        return true;

    QString dirPath = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation);

    QDir().mkpath(dirPath);

    QString path = dirPath + "/autoworkshop_vann.db";
    db.setDatabaseName(path);

    return db.open();
}

bool AutoWorkshopSql::isOpen() const
{
    return db.isValid() && db.isOpen();
}

void AutoWorkshopSql::close()
{
    if(db.isValid() && db.isOpen())
    {
        db.close();
    }
}

// create tables if not exist
bool AutoWorkshopSql::initSchema()
{
    lastDbError.clear();
    if(!isOpen())
    {
        lastDbError = "DB is not open.";
        return false;
    }

    qDebug() << "Db is open. Create tables if not existed...";

    // crate a query object
    QSqlQuery query(db);

    // users table
    if(!query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE NOT NULL, password TEXT NOT NULL);"))
    {
        lastDbError = query.lastError().text();
        return false;
    }

    // employees

    if(!query.exec("CREATE TABLE IF NOT EXISTS employees (em_id integer PRIMARY KEY AUTOINCREMENT, "
                   "name text NOT NULL, phone text, hour_pay integer, create_at text);"))
    {
        lastDbError = query.lastError().text();
        return false;
    }

    // emp_calendar
    if(!query.exec("CREATE TABLE IF NOT EXISTS emp_calendar (id INTEGER PRIMARY KEY AUTOINCREMENT, em_id INTEGER NOT NULL, "
                   "name TEXT NOT NULL, appoint_date TEXT, ticket_id INTEGER NOT NULL, customer TEXT, "
                   "slot0 INTEGER, slot1 INTEGER, slot2 INTEGER, slot3 INTEGER, slot4 INTEGER);"))
    {
        lastDbError = query.lastError().text();
        return false;
    }

    // tickets table
    if(!query.exec("CREATE TABLE IF NOT EXISTS tickets (id integer PRIMARY KEY AUTOINCREMENT, customer TEXT, brand text, model text, "
                   "regis_id text, emp_name TEXT, date text, slot0 int, slot1 int, slot2 int, slot3 int, slot4 int, "
                   "description text, status INTEGER, total_to_pay REAL);"))
    {
        lastDbError = query.lastError().text();
        return false;
    }

    // ticket_parts
    if(!query.exec("CREATE TABLE IF NOT EXISTS ticket_parts (ticket_id integer NOT NULL, part_name text, amount real, unit_price REAL);"))
    {
        lastDbError = query.lastError().text();
        return false;
    }

    // ticket_estimate
    if(!query.exec("CREATE TABLE IF NOT EXISTS ticket_estimate (ticket_id integer NOT NULL, "
                   "description text, expected_cost text, accepted integer);"))
    {
        lastDbError = query.lastError().text();
        return false;
    }


    qDebug() << "Tables created success: " << db.tables();

    return true;

}

// db level: provide api for user login verification
bool AutoWorkshopSql::verifyUser(const QString& username, const QString& password, int* userId, QString* role)
{
    lastDbError.clear();
    if(!db.isOpen())
    {
        lastDbError = "DB is not open.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE username=? AND password=? ");
    query.addBindValue(username); query.addBindValue(password);
    qDebug() << "connection name:" << db.connectionName();
    qDebug() << "querying" + db.databaseName();

    if(!query.exec())
    {
        lastDbError = query.lastError().text();
        return false;
    }
    qDebug() << "executed. isSelect=" << query.isSelect();

    if(!query.next())
    {
        lastDbError = "Invalid username or password.";
        return false;
    }

    if(userId) *userId = query.value(0).toInt();
    // if(role) *role = query.value(1).toString();
    return true;
}

bool AutoWorkshopSql::checkUserExist(const QString& username)
{
    lastDbError.clear();
    if (!db.isOpen())
    {
        lastDbError = "Db is not open.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec())
    {
        lastDbError = query.lastError().text();
        return false;
    }

    if (!query.next())
    {
        lastDbError = "username does not exist.";
        return false;
    }

    return true;

}

bool AutoWorkshopSql::createAccount(const QString& username, const QString& password)
{
    lastDbError.clear();
    if (!isOpen())
    {
        lastDbError = "Db is not open.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    query.addBindValue(username); query.addBindValue(password);
    if (!query.exec())
    {
        lastDbError = query.lastError().text();
        return false;
    }

    return true;
}

Ticket AutoWorkshopSql::getTicket(int ticketId)
{
    Ticket ticket;

    QSqlQuery query(db);
    query.prepare("select * from tickets where id =:ticketId");
    query.bindValue(":ticketId", ticketId);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return ticket;
    }

    while (query.next()) {
        ticket.id= query.value("id").toInt();
        ticket.customer = query.value("customer").toString();
        ticket.brand = query.value("brand").toString();
        ticket.model = query.value("model").toString();
        ticket.resgisId = query.value("regis_id").toString();

        ticket.empNames = query.value("emp_name").toString().split(", ");
        ticket.date = query.value("date").toString();
        ticket.timeSlots.append(query.value("slot0").toInt());
        ticket.timeSlots.append(query.value("slot1").toInt());
        ticket.timeSlots.append(query.value("slot2").toInt());
        ticket.timeSlots.append(query.value("slot3").toInt());
        ticket.timeSlots.append(query.value("slot4").toInt());
        ticket.description = query.value("description").toString();
        ticket.status = intToTicketStatus(query.value("status").toInt());
    }
    return ticket;
}

QList<Ticket> AutoWorkshopSql::filterTicketById(const QString &input)
{
    QList<Ticket> tickets;

    QSqlQuery query(db);
    query.prepare("select * from tickets where cast(id as text) like :input");
    query.bindValue(":input", "%" + input + "%");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return tickets; // Return an empty list if the query fails
    }

    while (query.next()) {
        Ticket ticket;

        ticket.id= query.value("id").toInt();
        ticket.customer = query.value("customer").toString();
        ticket.brand = query.value("brand").toString();
        ticket.model = query.value("model").toString();
        ticket.resgisId = query.value("regis_id").toString();

        ticket.empNames = query.value("emp_name").toString().split(", ");
        ticket.date = query.value("date").toString();
        ticket.timeSlots.append(query.value("slot0").toInt());
        ticket.timeSlots.append(query.value("slot1").toInt());
        ticket.timeSlots.append(query.value("slot2").toInt());
        ticket.timeSlots.append(query.value("slot3").toInt());
        ticket.timeSlots.append(query.value("slot4").toInt());
        ticket.description = query.value("description").toString();
        ticket.status = intToTicketStatus(query.value("status").toInt());

        tickets.append(ticket);
    }

    return tickets;
}

QList<Ticket> AutoWorkshopSql::getWeeklyTickets(const QDate& startDate, const QDate& endDate)
{
    QSqlQuery query(db);
    QString queryString = QString("select * from tickets where date >= '%1' and date <= '%2' order by date asc")
                              .arg(startDate.toString("yyyy-MM-dd"))
                              .arg(endDate.toString("yyyy-MM-dd"));
    QList<Ticket> tickets;
    // Execute the query
    if (!query.exec(queryString)) {
        qDebug() << "Database query error:" << query.lastError();
        return tickets;
    }

    // Process the results
    while (query.next()) {
        Ticket ticket;
        // Assuming Ticket is a struct or class you've defined, and you map the query result to it
        ticket.id = query.value("id").toInt();
        ticket.status = intToTicketStatus(query.value("status").toInt());
        ticket.empNames.append(query.value("emp_name").toString());

        ticket.date = query.value("date").toString();
        ticket.timeSlots.append(query.value("slot0").toInt());
        ticket.timeSlots.append(query.value("slot1").toInt());
        ticket.timeSlots.append(query.value("slot2").toInt());
        ticket.timeSlots.append(query.value("slot3").toInt());
        ticket.timeSlots.append(query.value("slot4").toInt());

        tickets.append(ticket);
    }

    return tickets;
}

bool AutoWorkshopSql::updateTicketStatus(const Ticket& ticket, TicketStatus newStatus)
{
    QSqlQuery query(db);
    QString queryString = QString("update tickets set status = %1 where id = %2")
                              .arg(ticketStatusToInt(newStatus))
                              .arg(ticket.id);
    qDebug() << queryString;

    if (!query.exec(queryString))
    {
        qDebug() << "Car_workshop_sql::updateTickeStatus Query failed:" << query.lastError();
        return false;
    }
    return true;
}

bool AutoWorkshopSql::updateTicketStatusById(int ticketId, int newStatus)
{
    QSqlQuery query(db);
    QString queryString = QString("update tickets set status = %1 where id = %2")
                              .arg(newStatus)
                              .arg(ticketId);
    qDebug() << queryString;

    if (!query.exec(queryString))
    {
        qDebug() << "Car_workshop_sql::updateTickeStatus Query failed:" << query.lastError();
        return false;
    }
    return true;
}


QString AutoWorkshopSql::getLastDbError() const
{
    return lastDbError;
}

QList<Ticket> AutoWorkshopSql::getAllTickets()
{
    QList<Ticket> tickets;

    QSqlQuery query("select * from tickets", db);
    while (query.next()) {
        qDebug() << "DB file:" << query.value(2).toString();
        Ticket ticket;
        ticket.id= query.value("id").toInt();
        ticket.customer = query.value("customer").toString();
        ticket.brand = query.value("brand").toString();
        ticket.model = query.value("model").toString();
        ticket.resgisId = query.value("regis_id").toString();
        //ticket.empNames
        ticket.empNames = query.value("emp_name").toString().split(", ");
        ticket.date = query.value("date").toString();
        ticket.timeSlots.append(query.value("slot0").toInt());
        ticket.timeSlots.append(query.value("slot1").toInt());
        ticket.timeSlots.append(query.value("slot2").toInt());
        ticket.timeSlots.append(query.value("slot3").toInt());
        ticket.timeSlots.append(query.value("slot4").toInt());
        ticket.description = query.value("description").toString();
        qDebug() << "Ticket status: " + query.value("status").toString();
        ticket.status = intToTicketStatus(query.value("status").toInt());

        tickets.append(ticket);
    }
    qDebug() << "==== Tickets fetched:" << tickets.size() << "====";

    for (int i = 0; i < tickets.size(); ++i) {
        const Ticket& t = tickets[i];
        qDebug()
            << "Ticket[" << i << "]"
            << "id=" << t.id
            << "customer=" << t.customer
            << "brand=" << t.brand
            << "model=" << t.model
            << "regisId=" << t.resgisId
            << "empNames=" << t.empNames
            << "date=" << t.date
            << "slots=" << t.timeSlots
            << "status=" << ticketStatusToString(t.status);
    }


    return tickets;
}

AutoWorkshopSql::~AutoWorkshopSql() = default;
