#ifndef PARSERLOGGER_H
#define PARSERLOGGER_H

#include "logentry.h"

#include <QDebug>

#include <memory>
#include <vector>

namespace parser {
class ParserLogger {
public:
    ParserLogger();

    std::vector<std::unique_ptr<LogEntry>>& getEntries();
    void addEntry(std::unique_ptr<LogEntry>&& entry);

    void debug(const QString& message);
    void info(const QString& message);
    void warning(const QString& message);
    void error(const QString& message);

    // operator <<(const LogEntry& entry);

private:
    std::vector<std::unique_ptr<LogEntry>> entries;
};
}

#endif // PARSERLOGGER_H
