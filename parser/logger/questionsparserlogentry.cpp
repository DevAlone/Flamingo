#include "questionsparserlogentry.h"

namespace parser {

QuestionsParserLogEntry::QuestionsParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path, long lineNumber, const QString& line)
    : ParserLogEntry(type, message, path, lineNumber, line)
{
    this->message = QString("(QuestionsParser) ") + this->message;
}
}
