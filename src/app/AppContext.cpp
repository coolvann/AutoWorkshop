#include "AppContext.h"
#include "data/AutoWorkshopSql.h"
#include <QDebug>

AppContext& AppContext::instance()
{
    static AppContext context;
    return context;
}

AppContext::AppContext(QObject* parent):QObject(parent)
{
    db = std::make_unique<AutoWorkshopSql>();
    ticketService = std::make_unique<TicketService>(db.get());
}

AutoWorkshopSql& AppContext::getDb()
{
    // if db open then return
    if(db->isOpen())
        return *db;

    // otherwise the create db
    QString path = "autoworkshop_vann.db";
    if(!db->openDb(path))
    {
        qCritical()<<"Failed to oprn db."<< db->getLastDbError();
    } else if(!db->initSchema())
    {   // create schema
        qCritical()<<"Failed to init schema." << db->getLastDbError();
    } else {
        qDebug()<<"Database is open: " << path;
    }
    return *db;
}

TicketService* AppContext::getTicketService()
{
    return ticketService.get();
}

// user session
void AppContext::setSession(const std::optional<UserSession>& session)
{
    m_session = session;
    emit sessionChanged();
}

const std::optional<UserSession>& AppContext::getSession() const
{
    return m_session;
}

void AppContext::clearSession()
{
    m_session = UserSession{};
    emit sessionChanged();
}

AppContext::~AppContext() = default;





