#ifndef PARSER_H
#define PARSER_H

#include "logger/parserlogger.h"

#include <QtCore>
#include <memory>

namespace parser {

class Parser {
public:
    void setLogger(std::shared_ptr<ParserLogger>& logger);

protected:
    std::shared_ptr<ParserLogger> logger;
    template <typename T, typename... Args>
    void logEntry(Args... args)
    {
        if (logger)
            logger->addEntry(std::make_unique<T>(args...));
    }
};

std::pair<QString, QString> getKeyValueFromString(const QString& str, bool* isOk, QChar delimiter = ':');
}

#endif // PARSER_H
