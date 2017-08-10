#ifndef MODULESPARSERLOGENTRY_H
#define MODULESPARSERLOGENTRY_H

#include "logentry.h"
#include "parserlogentry.h"

namespace parser {
class ModulesParserLogEntry : public ParserLogEntry {
public:
    ModulesParserLogEntry(
        LOG_ENTRY_TYPE type,
        const QString& message,
        const QString& path = "",
        long lineNumber = -1,
        const QString& line = "");
};
}
#endif // MODULESPARSERLOGENTRY_H
