#ifndef COURSESPARSERLOGENTRY_H
#define COURSESPARSERLOGENTRY_H

#include "logentry.h"

namespace parser {
class CoursesParserLogEntry : public LogEntry {
public:
    CoursesParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path = "");

    virtual QString toString() const;

protected:
    QString path;
    QString message;
};
}

#endif // COURSESPARSERLOGENTRY_H
