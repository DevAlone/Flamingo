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
