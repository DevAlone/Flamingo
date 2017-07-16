#include "pagesparserlogentry.h"

namespace parser {

PagesParserLogEntry::PagesParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path, long lineNumber, const QString& line, PagesParser::SECTION section)
    : ParserLogEntry(type, message, path, lineNumber, line)
{
    QString resultMessage = QString("(PagesParser) ") + this->message;
    switch (section) {
    case PagesParser::SECTION::INFO:
        resultMessage += "\n Current section is INFO\n";
        break;
    case PagesParser::SECTION::ANSWERS:
        resultMessage += "\n Current section is ANSWERS\n";
        break;
    default:
        break;
    }
    this->message = resultMessage;
}
}
