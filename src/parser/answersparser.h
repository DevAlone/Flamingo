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


#ifndef ANSWERSPARSER_H
#define ANSWERSPARSER_H

#include "parser.h"

#include "models/include.h"

namespace parser {
class AnswersParser : public Parser {
public:
    AnswersParser();

    // function can return empty pointer
    std::shared_ptr<Answer> parseAnswer(
        QString& string,
        QChar answerLetter,
        unsigned long baseLineNumber,
        QString path);

private:
    unsigned long baseLineNumber = 0;
    unsigned long lineNumber = 0;
    QString line;
    QString path;

    void insertKeyValue(std::map<QString, QString>& keyValueMap,
        std::vector<std::pair<QString, QString> >& keyValueVec,
        std::pair<QString, QString> buffer);
};
}

#endif // ANSWERSPARSER_H
