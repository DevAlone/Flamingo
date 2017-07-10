#ifndef QUESTIONSPARSERLOGENTRY_H
#define QUESTIONSPARSERLOGENTRY_H

#include "parser/questionsparser.h"
#include "parserlogentry.h"

namespace parser {
class QuestionsParserLogEntry : public ParserLogEntry {
public:
    QuestionsParserLogEntry(
        LOG_ENTRY_TYPE type,
        const QString& message,
        const QString& path = "",
        long lineNumber = -1,
        const QString& line = "",
        QuestionsParser::SECTION section = QuestionsParser::SECTION::NONE);

private:
    QuestionsParser::SECTION section;
};
}

#endif // QUESTIONSPARSERLOGENTRY_H
