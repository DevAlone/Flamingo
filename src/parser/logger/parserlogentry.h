#ifndef PARSERLOGENTRY_H
#define PARSERLOGENTRY_H

#include "logentry.h"

namespace parser {
class ParserLogEntry : public LogEntry {
public:
    ParserLogEntry(
        LOG_ENTRY_TYPE type,
        const QString& message,
        const QString& path = "",
        long lineNumber = -1,
        const QString& line = "");

    virtual QString toString() const;

protected:
    QString path;
    QString message;
    long lineNumber;
    QString line;
};
}

#endif // PARSERLOGENTRY_H
