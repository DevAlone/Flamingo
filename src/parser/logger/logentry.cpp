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


#include "logentry.h"

namespace parser {

LogEntry::LogEntry(LOG_ENTRY_TYPE type, const QString& message)
    : type(type)
    , message(message)
{
    time = QDateTime::currentDateTime();
}

LogEntry::~LogEntry()
{
}

QString LogEntry::toString() const
{
    QString result = time.toString();
    result += " ";
    switch (type) {
    case LOG_ENTRY_TYPE::DEBUG:
        result += "[DEBUG]";
        break;
    case LOG_ENTRY_TYPE::INFO:
        result += "[INFO]";
        break;
    case LOG_ENTRY_TYPE::WARNING:
        result += "[WARNING]";
        break;
    case LOG_ENTRY_TYPE::ERROR:
        result += "[ERROR]";
        break;
    }
    result += " ";
    result += message;

    return result;
}

LOG_ENTRY_TYPE LogEntry::getType() const
{
    return type;
}

QDateTime LogEntry::getTime() const
{
    return time;
}
}
