#ifndef COURSESPARSERLOGENTRY_H
#define COURSESPARSERLOGENTRY_H

#include "logentry.h"
#include "parserlogentry.h"

namespace parser {
class CoursesParserLogEntry : public ParserLogEntry {
public:
    CoursesParserLogEntry(
        LOG_ENTRY_TYPE type,
        const QString& message,
        const QString& path = "",
        long lineNumber = -1,
        const QString& line = "");

    virtual QString toString() const;
};
}

#endif // COURSESPARSERLOGENTRY_H
