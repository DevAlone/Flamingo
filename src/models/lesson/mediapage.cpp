#include "mediapage.h"

#include <exceptions/modelserializationerror.h>

MediaPage::MediaPage(std::map<QString, QString>& infoSection)
{
    {
        auto it = infoSection.find("source");
        if (it != infoSection.end())
            source = it->second;
    }
}

QJsonObject MediaPage::toJsonObject() const
{
    QJsonObject obj = Page::toJsonObject();

    QJsonArray jsonInfoSection;
    if (obj["info_section"].isArray()) {
        jsonInfoSection = obj["info_section"].toArray();
    } else
        throw ModelSerializationError(
            QObject::tr("error during serialization of MediaPage: "
                        "info_section wasn't found"));

    jsonInfoSection.push_back(QJsonObject{
        { "source", source } });

    obj["info_section"] = jsonInfoSection;

    return obj;
}

QString MediaPage::getSource() const
{
    return source;
}

void MediaPage::setSource(const QString& value)
{
    source = value;
}