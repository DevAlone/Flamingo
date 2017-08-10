#include "parserlogger.h"

namespace parser {
ParserLogger::ParserLogger()
{
}

std::vector<std::shared_ptr<LogEntry>>& ParserLogger::getEntries()
{
    return entries;
}

std::vector<std::shared_ptr<LogEntry>>& ParserLogger::getEntries(LOG_ENTRY_TYPE type)
{
    std::vector<std::shared_ptr<LogEntry>> result;

    for (auto& entry : entries) {
        if (entry->getType() == type)
            result.push_back(entry);
    }
    return result;
}

void ParserLogger::addEntry(std::shared_ptr<LogEntry>&& entry)
{
    entries.push_back(std::move(entry));
}

void ParserLogger::debug(const QString& message)
{
    entries.push_back(std::make_unique<LogEntry>(LOG_ENTRY_TYPE::DEBUG, message));
}
void ParserLogger::info(const QString& message)
{
    entries.push_back(std::make_unique<LogEntry>(LOG_ENTRY_TYPE::INFO, message));
}
void ParserLogger::warning(const QString& message)
{
    entries.push_back(std::make_unique<LogEntry>(LOG_ENTRY_TYPE::WARNING, message));
}
void ParserLogger::error(const QString& message)
{
    entries.push_back(std::make_unique<LogEntry>(LOG_ENTRY_TYPE::ERROR, message));
}
}
