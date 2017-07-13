#ifndef ANSWERSPARSERLOGENTRY_H
#define ANSWERSPARSERLOGENTRY_H

#include "parserlogentry.h"

namespace parser {

class AnswersParserLogEntry : public ParserLogEntry {
public:
    AnswersParserLogEntry(
        LOG_ENTRY_TYPE type,
        const QString& message,
        const QString& path = "",
        long lineNumber = -1,
        const QString& line = "");
};
}

#endif // ANSWERSPARSERLOGENTRY_H
