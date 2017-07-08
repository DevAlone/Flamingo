#include "coursesparserlogentry.h"

namespace parser {

CoursesParserLogEntry::CoursesParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path)
    : LogEntry(type)
    , path(path)
    , message(message)
{
}

QString CoursesParserLogEntry::toString() const
{
    QString result = LogEntry::toString();

    result += "(CoursesParser) ";
    result += message;
    if (path != "")
        result += "\r\npath: " + path;

    return result;
}
}
