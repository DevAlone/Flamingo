#include "questionsparserlogentry.h"

namespace parser {

QuestionsParserLogEntry::QuestionsParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path, long lineNumber, const QString& line, QuestionsParser::SECTION section)
    : ParserLogEntry(type, message, path, lineNumber, line)
{
    QString resultMessage = QString("(QuestionsParser) ") + this->message;
    switch (section) {
    case QuestionsParser::SECTION::INFO:
        resultMessage += "\n Current section is INFO\n";
        break;
    case QuestionsParser::SECTION::ANSWERS:
        resultMessage += "\n Current section is ANSWERS\n";
        break;
    default:
        break;
    }
    this->message = resultMessage;
}
}
