#include "logentry.h"

namespace parser {

LogEntry::LogEntry(LOG_ENTRY_TYPE type, const QString& message)
    : type(type)
    , message(message)
{
    time = QDateTime::currentDateTime();
}

LogEntry::~LogEntry()
{
}

QString LogEntry::toString() const
{
    QString result = time.toString();
    result += " ";
    switch (type) {
    case LOG_ENTRY_TYPE::DEBUG:
        result += "[DEBUG]";
        break;
    case LOG_ENTRY_TYPE::INFO:
        result += "[INFO]";
        break;
    case LOG_ENTRY_TYPE::WARNING:
        result += "[WARNING]";
        break;
    case LOG_ENTRY_TYPE::ERROR:
        result += "[ERROR]";
        break;
    }
    result += " ";
    result += message;

    return result;
}

LOG_ENTRY_TYPE LogEntry::getType() const
{
    return type;
}

QDateTime LogEntry::getTime() const
{
    return time;
}
}
