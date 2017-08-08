#include "textpage.h"

#include <exceptions/modelserializationerror.h>

#include <QDebug>

TextPage::TextPage(const std::map<QString, QString>& infoSection)
{
    auto contentIt = infoSection.find("text content");
    if (contentIt != infoSection.end()) {

        content.setText(contentIt->second);
    }
}

const QString& TextPage::getContent() const
{
    return content.getText();
}

QJsonObject TextPage::toJsonObject() const
{
    QJsonObject obj = Page::toJsonObject();

    QJsonArray jsonInfoSection;
    if (obj["info_section"].isArray()) {
        jsonInfoSection = obj["info_section"].toArray();
    } else
        throw ModelSerializationError(
            QObject::tr("error during serialization TextPage: "
                        "info_section wasn't found"));

    jsonInfoSection.push_back(content.toJsonObject());

    obj["info_section"] = jsonInfoSection;

    return obj;
}
