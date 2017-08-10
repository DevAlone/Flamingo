#ifndef QUESTIONSPARSERLOGENTRY_H
#define QUESTIONSPARSERLOGENTRY_H

#include "parser/pagesparser.h"
#include "parserlogentry.h"

namespace parser {
class PagesParserLogEntry : public ParserLogEntry {
public:
    PagesParserLogEntry(
        LOG_ENTRY_TYPE type,
        const QString& message,
        const QString& path = "",
        long lineNumber = -1,
        const QString& line = "",
        PagesParser::SECTION section = PagesParser::SECTION::NONE);

private:
    PagesParser::SECTION section;
};
}

#endif // QUESTIONSPARSERLOGENTRY_H
