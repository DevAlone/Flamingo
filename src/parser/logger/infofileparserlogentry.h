#ifndef INFOFILEPARSERLOGENTRY_H
#define INFOFILEPARSERLOGENTRY_H

#include "parserlogentry.h"


namespace parser {
class InfoFileParserLogEntry : public ParserLogEntry
{
public:
    InfoFileParserLogEntry(
            LOG_ENTRY_TYPE type,
            const QString& message,
            const QString& path = "",
            long lineNumber = -1,
            const QString& line = "");


};
}

#endif // INFOFILEPARSERLOGENTRY_H
