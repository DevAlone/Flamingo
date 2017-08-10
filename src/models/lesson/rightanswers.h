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


#ifndef RIGHTANSWERS_H
#define RIGHTANSWERS_H

#include <QtCore>

#include <set>

class RightAnswers {

public:
    static RightAnswers fromString(const QString& _expression);

    const std::set<QChar>& getAnswers() const;
    bool isAnswersRight(std::set<QChar> userAnswers) const;

    QString toString() const;
    QString toHumanString() const;

private:
    enum class EXPRESSION_TYPE {
        AND,
        OR
    };
    EXPRESSION_TYPE type;
    std::set<QChar> answers;
};

#endif // RIGHTANSWERS_H
