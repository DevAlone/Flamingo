#include "coursesparserlogentry.h"

#include <QObject>

namespace parser {

CoursesParserLogEntry::CoursesParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path, long lineNumber, const QString& line)
    : ParserLogEntry(type, message, path, lineNumber, line)
{
    this->message = QString("(CoursesParser) ") + this->message;
}

QString CoursesParserLogEntry::toString() const
{
    return ParserLogEntry::toString();
}
}
