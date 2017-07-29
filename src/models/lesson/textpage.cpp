#include "textpage.h"

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
    // TODO: call method of Page and serialize TextPage
    return Page::toJsonObject();
}

std::shared_ptr<TextPage> TextPage::fromJsonObject(const QJsonObject& obj)
{
    // TODO: jlkasfdlkafl;asdfldfsalsdafl;k
    return std::shared_ptr<TextPage>();
}
