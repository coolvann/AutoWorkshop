#ifndef LOG_H
#define LOG_H
#include <QLoggingCategory>

// app
Q_DECLARE_LOGGING_CATEGORY(logApp)

// ui
Q_DECLARE_LOGGING_CATEGORY(logUi)
Q_DECLARE_LOGGING_CATEGORY(logUiWidgetsAddEmp)

// service
Q_DECLARE_LOGGING_CATEGORY(logAuth)
Q_DECLARE_LOGGING_CATEGORY(logTicket)

// data
Q_DECLARE_LOGGING_CATEGORY(logDb)

#endif // LOG_H
