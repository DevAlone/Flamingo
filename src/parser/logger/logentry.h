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


#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <QDateTime>
#include <QString>

namespace parser {

// it's needed to prevent compiling errors on windows
#undef ERROR
enum class LOG_ENTRY_TYPE {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class LogEntry {
public:
    LogEntry(LOG_ENTRY_TYPE type, const QString& message = "");
    virtual ~LogEntry();

    virtual QString toString() const;

    LOG_ENTRY_TYPE getType() const;

    QDateTime getTime() const;

protected:
    LOG_ENTRY_TYPE type;
    QString message;
    QDateTime time;
};
}
#endif // LOGENTRY_H
