#include "page.h"
#include "htmlpage.h"
#include "textpage.h"

#include <exceptions/modelserializationerror.h>
#include <exceptions/pagecreatingerror.h>

std::shared_ptr<Page> Page::createPage(
    unsigned pageNumber,
    std::map<QString, QString>& infoSection,
    std::map<QChar, std::shared_ptr<Answer>>& answers)
{
    static const std::map<QString, PAGE_TYPE> pageTypes = {
        { QString("text"), PAGE_TYPE::TEXT },
        { QString("html"), PAGE_TYPE::HTML },
    };

    PAGE_TYPE type = PAGE_TYPE::TEXT;

    auto typeIt = infoSection.find("type");
    if (typeIt != infoSection.end()) {
        auto enumIt = pageTypes.find(typeIt->second);
        if (enumIt != pageTypes.end())
            type = enumIt->second;
        else
            throw PageCreatingError(
                QObject::tr("Unable to recognize type of page: ")
                + typeIt->second);
    }

    std::shared_ptr<Page> page;

    switch (type) {
    case PAGE_TYPE::TEXT:
        page = std::make_shared<TextPage>(infoSection);
        break;
    case PAGE_TYPE::HTML:
        page = std::make_shared<HtmlPage>(infoSection);
        break;
    }

    page->type = type;
    page->number = pageNumber;

    auto rightAnswersIt = infoSection.find("right answers");
    if (rightAnswersIt != infoSection.end()) {
        page->rightAnswers = RightAnswers::fromString(rightAnswersIt->second);
        const auto& answers = page->rightAnswers.getAnswers();
        if (answers.size() < 1)
            throw PageCreatingError(
                QObject::tr("You have to set at least one right answer: ")
                + rightAnswersIt->second);

        // TODO: check that all right answers exists
    }

    page->answers = answers;

    // TODO: do fucking checks
    //    if (page->answers) {
    //        if (page->answers.size() > 0) {
    //            if (!page->rightAnswers || page->rightAnswers->getAnswers().size() < 1)
    //                throw PageCreatingError(
    //                    QObject::tr("You have to set at least one right answer"));
    //        }
    //    }

    //    if (page->rightAnswers || page->rightAnswers->getAnswers().size() > 0) {
    //        if (page->answers.size() < 1)
    //            throw PageCreatingError(
    //                QObject::tr("You have to set at least one answer"));
    //    }

    return page;
}

unsigned Page::getNumber() const
{
    return number;
}

PAGE_TYPE Page::getType() const
{
    return type;
}

const std::map<QChar, std::shared_ptr<Answer>>& Page::getAnswers() const
{
    return answers;
}

QJsonObject Page::toJsonObject() const
{
    QJsonObject obj;

    obj["number"] = QJsonValue(QString::number(number));
    obj["type"] = QString::number(int(type));

    QJsonArray jsonAnswers;

    for (auto& answer : answers) {
        jsonAnswers.push_back(QJsonObject{
            { "answer_letter", QString(answer.first) },
            { "answer", answer.second->toJsonObject() } });
    }
    obj["answers"] = jsonAnswers;

    obj["right_answers"] = rightAnswers.toJsonObject();

    return obj;
}

std::shared_ptr<Page> Page::fromJsonObject(const QJsonObject& obj)
{
    // TODO: use fabric method?

    std::shared_ptr<Page> page = std::make_shared<Page>();

    if (obj["number"].isString()) {
        unsigned number;
        bool isOk;
        number = obj["number"].toString().toUInt(&isOk);
        if (!isOk)
            throw ModelSerializationError(
                QObject::tr("page number is not a number"));
        page->number = number;
    } else
        throw ModelSerializationError(
            QObject::tr("page number is not exist or is not a json string"));

    if (obj["type"].isString()) {
        int type;
        bool isOk;
        type = obj["type"].toString().toInt(&isOk);
        if (!isOk)
            throw ModelSerializationError(
                QObject::tr("page type is not a number"));

        PAGE_TYPE pageType = static_cast<PAGE_TYPE>(type);

        if (pageType < PAGE_TYPE::TEXT || pageType >= PAGE_TYPE::PAGE_TYPE_COUNT)
            throw ModelSerializationError(
                QObject::tr("page type is not valid type"));

        page->type = pageType;
    } else
        throw ModelSerializationError(
            QObject::tr("page type is not exist or is not a json string"));

    QJsonArray jsonAnswers;

    if (obj["answers"].isArray())
        jsonAnswers = obj["answers"].toArray();
    else
        throw ModelSerializationError(
            QObject::tr("page answers is not exist or is not a json array"));

    for (auto jsonAnswer : jsonAnswers) {
        QJsonObject jsonAnswerPair;

        if (jsonAnswer.isObject())
            jsonAnswerPair = jsonAnswer.toObject();
        else
            throw ModelSerializationError(
                QObject::tr("json_answers doesn't exist or is not an json object"));

        std::pair<QChar, std::shared_ptr<Answer>> answerPair;

        if (jsonAnswerPair["answer_letter"].isString()) {
            QString str = jsonAnswerPair["answer_letter"].toString();
            if (str.size() != 1)
                throw ModelSerializationError(
                    QObject::tr("answer letter cannot be string"));
            answerPair.first = str[0];
        } else
            throw ModelSerializationError(
                QObject::tr("answer_letter doesn't exist or isn't a json string"));

        if (jsonAnswerPair["answer"].isObject()) {
            answerPair.second = Answer::fromJsonObject(jsonAnswerPair["answer"].toObject());
        } else
            throw ModelSerializationError(
                QObject::tr("answer doesn't exist or isn't an json object"));

        if (page->answers.find(answerPair.first) != page->answers.end())
            throw ModelSerializationError(
                QObject::tr("attempting to add more than one answer with same nubmer"));

        page->answers.insert(answerPair);
    }

    if (obj["right_answers"].isObject()) {
        page->rightAnswers = RightAnswers::fromJsonObject(obj["right_answers"].toObject());
    } else
        throw ModelSerializationError(
            QObject::tr("right_answers doesn't exist or isn't an object"));

    // TODO: parse subclass depend on type

    return page;
}
