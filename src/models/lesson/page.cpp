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


#include "page.h"
#include "audiopage.h"
#include "htmlpage.h"
#include "imagepage.h"
#include "mixedpage.h"
#include "textpage.h"
#include "videopage.h"

#include <exceptions/modelerror.h>
#include <exceptions/modelserializationerror.h>
#include <exceptions/pagecreatingerror.h>

std::shared_ptr<Page> Page::createPage(unsigned pageNumber,
    std::map<QString, QString>& infoSectionMap,
    std::vector<std::pair<QString, QString>>& infoSectionVec,
    std::map<QChar, std::shared_ptr<Answer>>& answers)
{

    PAGE_TYPE type = PAGE_TYPE::TEXT;

    auto typeIt = infoSectionMap.find("type");
    if (typeIt != infoSectionMap.end()) {
        auto enumIt = pageTypesMap.find(typeIt->second);
        if (enumIt != pageTypesMap.end())
            type = enumIt->second;
        else
            throw PageCreatingError(
                QObject::tr("Unable to recognize type of page: ")
                + typeIt->second);
    }

    std::shared_ptr<Page> page;

    switch (type) {
    case PAGE_TYPE::TEXT:
        page = std::make_shared<TextPage>(infoSectionMap);
        break;
    case PAGE_TYPE::HTML:
        page = std::make_shared<HtmlPage>(infoSectionMap);
        break;
    case PAGE_TYPE::IMAGE:
        page = std::make_shared<ImagePage>(infoSectionMap);
        break;
    case PAGE_TYPE::AUDIO:
        page = std::make_shared<AudioPage>(infoSectionMap);
        break;
    case PAGE_TYPE::VIDEO:
        page = std::make_shared<VideoPage>(infoSectionMap);
        break;
    case PAGE_TYPE::MIXED:
        page = std::make_shared<MixedPage>(infoSectionMap, infoSectionVec);
        break;
    }

    page->type = type;
    page->number = pageNumber;

    auto rightAnswersIt = infoSectionMap.find("right answers");
    if (rightAnswersIt != infoSectionMap.end()) {
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

    QString typeString = "";

    for (auto& keyValue : pageTypesMap) {
        if (keyValue.second == type) {
            typeString = keyValue.first;
            break;
        }
    }
    if (typeString.isEmpty())
        throw ModelSerializationError(
            QObject::tr("Undefined type"));

    QJsonArray jsonInfoSection;

    jsonInfoSection.push_back(QJsonObject{
        { "type", typeString } });

    QJsonArray jsonAnswers;

    for (auto& answer : answers) {
        jsonAnswers.push_back(QJsonObject{
            { "answer_letter", QString(answer.first) },
            { "answer", answer.second->toJsonObject() } });
    }

    obj["answers"] = jsonAnswers;

    if (rightAnswers.getAnswers().size() > 0)
        jsonInfoSection.push_back(QJsonObject{
            { "right answers", rightAnswers.toString() } });

    obj["info_section"] = jsonInfoSection;

    obj["completeness"] = QJsonValue(QString::number(getCompleteness()));

    return obj;
}

std::shared_ptr<Page> Page::fromJsonObject(const QJsonObject& obj)
{

    unsigned pageNumber;

    if (obj["number"].isString()) {
        bool isOk;
        pageNumber = obj["number"].toString().toUInt(&isOk);
        if (!isOk)
            throw ModelSerializationError(
                QObject::tr("page number is not a number"));
    } else
        throw ModelSerializationError(
            QObject::tr("page number is not exist or is not a json string"));

    std::map<QString, QString> infoSectionMap;
    std::vector<std::pair<QString, QString>> infoSectionVec;

    QJsonArray jsonInfoSection;

    if (obj["info_section"].isArray()) {
        jsonInfoSection = obj["info_section"].toArray();
    } else
        throw ModelSerializationError(
            QObject::tr("page info_section dosn't exist or isn't an array"));

    for (auto obj : jsonInfoSection) {
        if (obj.isObject()) {
            auto jsonObj = obj.toObject();
            for (auto& key : jsonObj.keys()) {
                if (jsonObj[key].isString()) {
                    auto pair = std::make_pair<QString, QString>(
                        QString(key), jsonObj[key].toString());

                    infoSectionMap.insert(pair);
                    infoSectionVec.push_back(pair);
                } else
                    throw ModelSerializationError(
                        QObject::tr("page info_section object contain not string type"));
            }
        } else
            throw ModelSerializationError(
                QObject::tr("page info_section contains not object"));
    }

    std::map<QChar, std::shared_ptr<Answer>> answers;

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
                QObject::tr("answer doesn't exist or isn't a json object"));

        if (answers.find(answerPair.first) != answers.end())
            throw ModelSerializationError(
                QObject::tr("attempting to add more than one answer with same nubmer"));

        answers.insert(answerPair);
    }

    std::shared_ptr<Page> page = createPage(
        pageNumber,
        infoSectionMap,
        infoSectionVec,
        answers);

    if (obj["completeness"].isString()) {
        bool isOk;
        int value = obj["completeness"].toString().toInt(&isOk);
        if (!isOk || value < 0)
            throw QObject::tr("completeness isn't a positive number");
        page->setCompleteness(value);
    } else
        throw ModelSerializationError(
            QObject::tr("completeness doesn't exist or isn't a json string"));

    return page;
}

const RightAnswers& Page::getRightAnswers() const
{
    return rightAnswers;
}

unsigned char Page::getCompleteness() const
{
    return completeness;
}

void Page::setCompleteness(unsigned char value)
{
    if (value > 100)
        throw ModelError(
            QObject::tr("completeness can't be bigger than 100"));

    completeness = value;
}
