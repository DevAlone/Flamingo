// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
