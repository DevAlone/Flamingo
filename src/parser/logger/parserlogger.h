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

    std::vector<std::shared_ptr<LogEntry>>& getEntries();
    std::vector<std::shared_ptr<LogEntry>>& getEntries(LOG_ENTRY_TYPE type);

    void addEntry(std::shared_ptr<LogEntry>&& entry);

    void debug(const QString& message);
    void info(const QString& message);
    void warning(const QString& message);
    void error(const QString& message);

    // operator <<(const LogEntry& entry);

private:
    std::vector<std::shared_ptr<LogEntry>> entries;
};
}

#endif // PARSERLOGGER_H
