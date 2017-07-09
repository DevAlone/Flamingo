#ifndef QUESTIONSPARSERLOGENTRY_H
#define QUESTIONSPARSERLOGENTRY_H

#include "parserlogentry.h"

namespace parser {
class QuestionsParserLogEntry : public ParserLogEntry {
public:
    QuestionsParserLogEntry(
        LOG_ENTRY_TYPE type,
        const QString& message,
        const QString& path = "",
        long lineNumber = -1,
        const QString& line = "");
};
}

#endif // QUESTIONSPARSERLOGENTRY_H
