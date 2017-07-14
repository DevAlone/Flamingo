#include "answer.h"
#include "htmlanswer.h"
#include "textanswer.h"

#include <exceptions/answercreatingerror.h>

#include <QObject>

Answer::Answer()
{
}

std::shared_ptr<Answer> Answer::createAnswer(
    QChar letter,
    std::map<QString, QString>& keyValueMap,
    std::vector<std::pair<QString, QString> >& keyValueVec)
{
    // TODO: change it
    static const std::map<QString, ANSWER_TYPE> answerTypes = {
        { QString("text"), ANSWER_TYPE::TEXT },
        { QString("html"), ANSWER_TYPE::HTML },
    };

    ANSWER_TYPE type = ANSWER_TYPE::TEXT;

    auto typeIt = keyValueMap.find("type");
    if (typeIt != keyValueMap.end()) {
        auto enumIt = answerTypes.find(typeIt->second);
        if (enumIt != answerTypes.end())
            type = enumIt->second;
        else
            throw AnswerCreatingError(
                QObject::tr("Unable ro recognize type of answer: ")
                + typeIt->second);
    }

    std::shared_ptr<Answer> answer;

    switch (type) {
    case ANSWER_TYPE::TEXT:
        answer = std::make_shared<TextAnswer>(keyValueMap, keyValueVec);
        break;
    case ANSWER_TYPE::HTML:
        answer = std::make_shared<HtmlAnswer>(keyValueMap, keyValueVec);
        break;
    }

    answer->type = type;
    answer->letter = letter;

    return answer;
}

ANSWER_TYPE Answer::getType() const
{
    return type;
}
