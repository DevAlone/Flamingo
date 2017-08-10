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


#ifndef LESSONSPARSER_H
#define LESSONSPARSER_H

#include "logger/parserlogger.h"
#include "models/lesson/lesson.h"
#include "parser.h"

#include <QObject>
#include <QtCore>

#include <memory>

namespace parser {
class LessonsParser : public Parser {
public:
    std::shared_ptr<Lesson> parseFile(const QString& path);

    enum class SECTION {
        NONE,
        INFO,
        PAGES
    };

private:
    SECTION section = SECTION::INFO;
    unsigned long lineNumber = 0;
    QString path;

    void parseInfoSection(std::shared_ptr<Lesson>& lesson, QString& line, QTextStream& stream);
    void parsePagesSection(std::shared_ptr<Lesson>& lesson, QString& line, QTextStream& stream);

    // TODO: удалить эту функцию, оставить только tryToChangeSection
    bool isSection(const QString& line) const;
    bool tryToChangeSection(const QString& line);
};
}

#endif // LESSONSPARSER_H
