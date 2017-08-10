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



#include <exceptions/pagecreatingerror.h>

RightAnswers RightAnswers::fromString(const QString& _expression)
{
    QString expression = _expression.simplified();

    RightAnswers result;
    // check right answers string
    bool andCondition = expression.contains('&');
    bool orCondition = expression.contains('|');

    if (andCondition && orCondition)
        throw PageCreatingError(
            QObject::tr("Right answers can contain only & or |, not both: ")
            + expression);

    if (andCondition) {
        result.type = EXPRESSION_TYPE::AND;
        QStringList rightAnswersList = expression.split('&', QString::SkipEmptyParts);
        for (auto& value : rightAnswersList) {
            value = value.simplified();
            if (value.size() > 0)
                result.answers.insert(value.at(0));
        }
    } else if (orCondition) {
        result.type = EXPRESSION_TYPE::OR;
        QStringList rightAnswersList = expression.split('|', QString::SkipEmptyParts);
        for (auto& value : rightAnswersList) {
            value = value.simplified();
            if (value.size() > 0)
                result.answers.insert(value.at(0));
        }
    } else {
        result.type = EXPRESSION_TYPE::AND;
        if (expression.size() > 0)
            result.answers.insert(expression[0]);
    }

    return result;
}

const std::set<QChar>& RightAnswers::getAnswers() const
{
    return answers;
}

bool RightAnswers::isAnswersRight(std::set<QChar> userAnswers) const
{

    if (type == EXPRESSION_TYPE::AND) {
        if (userAnswers.size() != this->answers.size())
            return false;

        for (auto& rightAnswer : this->answers) {
            if (userAnswers.find(rightAnswer) == userAnswers.end())
                return false;
        }

        return true;
    } else if (type == EXPRESSION_TYPE::OR) {
        if (userAnswers.size() == 0)
            return false;

        for (auto& userAnswer : userAnswers) {
            if (answers.find(userAnswer) == answers.end())
                return false;
        }

        return true;
    }

    return false;
    //    std::vector<QChar> intersection;

    //    std::set_intersection(this->answers.cbegin(), this->answers.cend(),
    //        answers.cbegin(), answers.cend(),
    //        std::back_inserter(intersection));
    //    // TODO: do it

    //    if (type == EXPRESSION_TYPE::AND)
    //        return intersection.size() == this->answers.size();
    //    else if (type == EXPRESSION_TYPE::OR)
    //        return intersection.size() > 0;

    //    return false;
}

QString RightAnswers::toString() const
{
    QString result = "";
    bool isFirst = true;
    for (auto& value : answers) {
        if (!isFirst)
            result += type == EXPRESSION_TYPE::AND ? "&" : "|";

        result += value;

        if (isFirst)
            isFirst = false;
    }
    return result;
}

QString RightAnswers::toHumanString() const
{
    QString result = toString();

    result.replace("|", QObject::tr(" or "));
    result.replace("&", QObject::tr(" and "));

    return result;
}
