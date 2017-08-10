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


#include "parserlogentry.h"

#include <QObject>

namespace parser {
ParserLogEntry::ParserLogEntry(LOG_ENTRY_TYPE type, const QString& message, const QString& path, long lineNumber, const QString& line)
    : LogEntry(type)
    , path(path)
    , message(message)
    , lineNumber(lineNumber)
    , line(line)
{
}

QString ParserLogEntry::toString() const
{
    QString result = LogEntry::toString();

    result += message;
    if (path != "")
        result += QObject::tr("\r\npath: ") + path + "\r\n";
    if (lineNumber >= 0 || line != "") {
        result += QObject::tr("Current line is line");
        if (lineNumber >= 0)
            result += QObject::tr(" number ") + QString::number(lineNumber);
        if (line != "")
            result += ": \"" + line + "\"";
    }

    return result;
}
}
