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


#ifndef PAGESPARSER_H
#define PAGESPARSER_H

#include "parser.h"

#include "models/include.h"

namespace parser {
class PagesParser : public Parser {
public:
    PagesParser();

    /// function can return empty smart pointer.
    /// Check it before using.
    std::shared_ptr<Page> parsePage(QString& string,
        unsigned pageNumber,
        unsigned long baseLineNumber, const QString& path);

    enum class SECTION {
        NONE,
        INFO,
        ANSWERS
    };

private:
    SECTION section = SECTION::INFO;
    unsigned long baseLineNumber = 0;
    unsigned long lineNumber = 0;
    QString path;
    QString line;

    bool tryToChangeSection(const QString& line);

    // TODO: add vector
    void parseInfoSection(std::map<QString, QString>& infoSectionMap, std::vector<std::pair<QString, QString> > &infoSectionVec, QString& line, QTextStream& stream);

    void addAnswerToMap(std::map<QChar, std::shared_ptr<Answer>>& answersMap,
        QChar answerLetter,
        QString& answerBuffer);

    void parseAnswersSection(std::map<QChar, std::shared_ptr<Answer>>& answersMap, QString& line, QTextStream& stream);
};
}

#endif // PAGESPARSER_H
