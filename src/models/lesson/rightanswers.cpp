#include "rightanswers.h"

#include <exceptions/pagecreatingerror.h>

RightAnswers RightAnswers::fromString(const QString& expression)
{
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
        for (auto& value : rightAnswersList)
            if (value.size() > 0)
                result.answers.insert(value.at(0));
    } else if (orCondition) {
        result.type = EXPRESSION_TYPE::OR;
        QStringList rightAnswersList = expression.split('|', QString::SkipEmptyParts);
        for (auto& value : rightAnswersList)
            if (value.size() > 0)
                result.answers.insert(value.at(0));
    } else {
        if (expression.size() > 0)
            result.answers.insert(expression[0]);
    }

    return result;
}

const std::set<QChar>& RightAnswers::getAnswers() const
{
    return answers;
}

bool RightAnswers::isAnswersRight(std::set<QChar> answers) const
{
    std::vector<int> intersection;

    //        std::set_intersection(this->answers.cbegin(), this->answers.cend(),
    //            answers.begin(), answers.end(),
    //            std::back_inserter(intersection));
    // TODO: do it

    if (type == EXPRESSION_TYPE::AND)
        return intersection.size() == answers.size();
    else if (type == EXPRESSION_TYPE::OR)
        return intersection.size() > 0;

    return false;
}

QString RightAnswers::toString() const
{
    QString result = "";
    bool isFirst = true;
    for (auto& value : answers) {
        if (isFirst)
            isFirst = false;
        if (!isFirst)
            result += type == EXPRESSION_TYPE::AND ? "&" : "|";
        result += value;
    }
    return result;
}
