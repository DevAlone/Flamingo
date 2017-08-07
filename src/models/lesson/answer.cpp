#include "answer.h"
#include "audioanswer.h"
#include "htmlanswer.h"
#include "imageanswer.h"
#include "textanswer.h"
#include "videoanswer.h"

#include <exceptions/answercreatingerror.h>
#include <exceptions/modelserializationerror.h>

#include <QJsonArray>
#include <QObject>

Answer::Answer()
{
}

Answer::~Answer()
{
}

std::shared_ptr<Answer> Answer::createAnswer(
    std::map<QString, QString>& keyValueMap,
    std::vector<std::pair<QString, QString>>& keyValueVec)
{
    ANSWER_TYPE type = ANSWER_TYPE::TEXT;

    auto typeIt = keyValueMap.find("type");
    if (typeIt != keyValueMap.end()) {
        auto enumIt = answerTypesMap.find(typeIt->second);
        if (enumIt != answerTypesMap.end())
            type = enumIt->second;
        else
            throw AnswerCreatingError(
                QObject::tr("Unable ro recognize type of answer: ")
                + typeIt->second);
    }

    std::shared_ptr<Answer> answer;

    switch (type) {
    case ANSWER_TYPE::TEXT:
        answer = std::make_shared<TextAnswer>(keyValueMap);
        break;
    case ANSWER_TYPE::HTML:
        answer = std::make_shared<HtmlAnswer>(keyValueMap);
        break;
    case ANSWER_TYPE::IMAGE:
        answer = std::make_shared<ImageAnswer>(keyValueMap);
        break;
    case ANSWER_TYPE::AUDIO:
        answer = std::make_shared<AudioAnswer>(keyValueMap);
        break;
    case ANSWER_TYPE::VIDEO:
        answer = std::make_shared<VideoAnswer>(keyValueMap);
        break;
    }

    answer->type = type;

    return answer;
}

ANSWER_TYPE Answer::getType() const
{
    return type;
}

QJsonObject Answer::toJsonObject() const
{
    QJsonObject obj;

    QString typeString = "";

    for (auto& keyValue : answerTypesMap) {
        if (keyValue.second == type) {
            typeString = keyValue.first;
            break;
        }
    }
    if (typeString.isEmpty())
        throw ModelSerializationError(
            QObject::tr("Undefined type of answer"));

    QJsonArray jsonInfoSection;

    jsonInfoSection.push_back(QJsonObject{
        { "type", typeString } });

    obj["info_section"] = jsonInfoSection;

    return obj;
}

std::shared_ptr<Answer> Answer::fromJsonObject(const QJsonObject& obj)
{
    std::map<QString, QString> keyValueMap;
    std::vector<std::pair<QString, QString>> keyValueVec;

    QJsonArray jsonInfoSection;

    if (obj["info_section"].isArray()) {
        jsonInfoSection = obj["info_section"].toArray();
    } else
        throw ModelSerializationError(
            QObject::tr("answer info_section doesn't exist or isn't an array"));

    for (auto obj : jsonInfoSection) {
        if (obj.isObject()) {
            auto jsonObj = obj.toObject();
            for (auto& key : jsonObj.keys()) {
                if (jsonObj[key].isString()) {
                    auto pair = std::make_pair<QString, QString>(
                        QString(key), jsonObj[key].toString());

                    keyValueMap.insert(pair);
                    keyValueVec.push_back(pair);

                } else
                    throw ModelSerializationError(
                        QObject::tr("answer info_section contains not string type"));
            }
        } else
            throw ModelSerializationError(
                QObject::tr("answer info_section contains not object"));
    }

    return createAnswer(keyValueMap, keyValueVec);
}
