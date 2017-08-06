#include "mediaanswer.h"

#include <exceptions/modelserializationerror.h>

#include <QJsonArray>
#include <QObject>

MediaAnswer::MediaAnswer(const std::map<QString, QString>& keyValueMap)
{
    {
        auto it = keyValueMap.find("source");
        if (it != keyValueMap.end())
            source = it->second;
    }
}

QJsonObject MediaAnswer::toJsonObject() const
{
    QJsonObject obj = Answer::toJsonObject();

    QJsonArray jsonInfoSection;
    if (obj["info_section"].isArray())
        jsonInfoSection = obj["info_section"].toArray();
    else
        throw ModelSerializationError(
            QObject::tr("error during serialization MediaAnswer: "
                        "info_section wasn't found"));
    jsonInfoSection.push_back(QJsonObject{
        { "source", source },
    });

    obj["info_section"] = jsonInfoSection;

    return obj;
}

QString MediaAnswer::getSource() const
{
    return source;
}

void MediaAnswer::setSource(const QString& value)
{
    source = value;
}
