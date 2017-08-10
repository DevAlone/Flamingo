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


#ifndef PARSER_H
#define PARSER_H

#include "logger/parserlogger.h"

#include <QtCore>
#include <memory>

namespace parser {

class Parser {
public:
    void setLogger(std::shared_ptr<ParserLogger>& logger);
    std::shared_ptr<ParserLogger> getLogger();

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
