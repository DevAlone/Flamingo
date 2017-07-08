#include "lessonsparserlogentry.h"

namespace parser {
LessonsParserLogEntry::LessonsParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path, long lineNumber, const QString& line)
    : ParserLogEntry(type, message, path, lineNumber, line)
{
    this->message = QString("(LessonsParser) ") + this->message;
}
}
