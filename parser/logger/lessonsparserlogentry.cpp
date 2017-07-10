#include "lessonsparserlogentry.h"
#include "parser/lessonsparser.h"

namespace parser {
LessonsParserLogEntry::LessonsParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path, long lineNumber, const QString& line, LessonsParser::SECTION section)
    : ParserLogEntry(type, message, path, lineNumber, line)
    , section(section)
{
    QString resultMessage = QString("(LessonsParser) ") + this->message;
    switch (section) {
    case LessonsParser::SECTION::INFO:
        resultMessage += "\n Current section is DESCRIPTION\n";
        break;
    case LessonsParser::SECTION::QUESTIONS:
        resultMessage += "\n Current section is QUESTIONS\n";
        break;
    default:
        break;
    }

    this->message = resultMessage;
}
}
