#include "mixedanswer.h"

#include <QJsonArray>
#include <QObject>

#include <exceptions/modelserializationerror.h>

MixedAnswer::MixedAnswer(
    const std::map<QString, QString>& keyValueMap,
    const std::vector<std::pair<QString, QString>>& keyValueVec)
{
    for (auto& pair : keyValueVec)
        if (auto content = Content::fromKeyValue(pair.first, pair.second))
            contents.push_back(content);
}

QJsonObject MixedAnswer::toJsonObject() const
{
    QJsonObject obj = Answer::toJsonObject();

    QJsonArray jsonInfoSection;
    if (obj["info_section"].isArray())
        jsonInfoSection = obj["info_section"].toArray();
    else
        throw ModelSerializationError(
            QObject::tr("error during serialization MixedAnswer: "
                        "info_section wasn't found"));

    for (auto& content : contents)
        jsonInfoSection.push_back(content->toJsonObject());

    obj["info_section"] = jsonInfoSection;

    return obj;
}

const std::vector<std::shared_ptr<Content>>& MixedAnswer::getContents() const
{
    return contents;
}
