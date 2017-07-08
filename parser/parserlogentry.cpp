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
        result += QObject::tr("Error ocurred in line");
        if (lineNumber >= 0)
            result += QObject::tr(" number ") + QString::number(lineNumber);
        if (line != "")
            result += ": \"" + line + "\"";
    }

    return result;
}
}
