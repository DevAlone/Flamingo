#include "textanswer.h"

#include <exceptions/modelserializationerror.h>

#include <QJsonArray>
#include <QObject>

TextAnswer::TextAnswer(const std::map<QString, QString>& keyValueMap)
{
    auto contentIt = keyValueMap.find("content");
    if (contentIt != keyValueMap.end())
        content.setText(contentIt->second);
}

const QString& TextAnswer::getContent() const
{
    return content.getText();
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
        { "content", content.getText() } });

    obj["info_section"] = jsonInfoSection;

    return obj;
}
