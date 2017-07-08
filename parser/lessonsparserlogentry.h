#ifndef LESSONSPARSERLOGENTRY_H
#define LESSONSPARSERLOGENTRY_H

#include "parserlogentry.h"

namespace parser {
class LessonsParserLogEntry : public ParserLogEntry {
public:
    LessonsParserLogEntry(
        LOG_ENTRY_TYPE type,
        const QString& message,
        const QString& path = "",
        long lineNumber = -1,
        const QString& line = "");
};
}

#endif // LESSONSPARSERLOGENTRY_H
