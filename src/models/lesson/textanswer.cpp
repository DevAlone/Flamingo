#include "textanswer.h"

#include <exceptions/modelserializationerror.h>

#include <QJsonArray>
#include <QObject>

TextAnswer::TextAnswer(std::map<QString, QString> keyValueMap,
    std::vector<std::pair<QString, QString> >& keyValueVec)
{
    auto contentIt = keyValueMap.find("content");
    if (contentIt != keyValueMap.end())
        content = contentIt->second;
}

const QString& TextAnswer::getContent() const
{
    return content;
}

QJsonObject TextAnswer::toJsonObject() const
{
    QJsonObject obj = Answer::toJsonObject();

    QJsonArray jsonInfoSection;
    if (obj["info_section"].isArray()) {
        jsonInfoSection = obj["info_section"].toArray();
    } else
        throw ModelSerializationError(
            QObject::tr("error during serialization TextAnswer:"
                        "info_section wasn't found"));
    jsonInfoSection.push_back(QJsonObject{
        { "content", content } });

    return obj;
}
