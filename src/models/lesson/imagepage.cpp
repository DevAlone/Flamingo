#include "imagepage.h"

ImagePage::ImagePage(std::map<QString, QString>& infoSection)
    : MediaPage(infoSection)
{
}

QJsonObject ImagePage::toJsonObject() const
{
    return MediaPage::toJsonObject();
}
