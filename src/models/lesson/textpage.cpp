#include "textpage.h"

#include <exceptions/modelserializationerror.h>

TextPage::TextPage(std::map<QString, QString>& infoSection)
{
    auto contentIt = infoSection.find("content");
    if (contentIt != infoSection.end()) {

        content = contentIt->second;
    }
}

const QString& TextPage::getContent() const
{
    return content;
}

QJsonObject TextPage::toJsonObject() const
{
    QJsonObject obj = Page::toJsonObject();

    QJsonArray jsonInfoSection;
    if (obj["info_section"].isArray()) {
        jsonInfoSection = obj["info_section"].toArray();
    } else
        throw ModelSerializationError(
            QObject::tr("error during serialization TextPage:"
                        "info_section wasn't found"));

    jsonInfoSection.push_back(QJsonObject{
        { "content", content } });

    obj["info_section"] = jsonInfoSection;

    return obj;
}
