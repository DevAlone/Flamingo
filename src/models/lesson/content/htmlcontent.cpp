#include "htmlcontent.h"

HtmlContent::HtmlContent(const QString& html)
    : TextContent(html)
{
    type = CONTENT_TYPE::HTML;
}

const QString& HtmlContent::getHtml()
{
    return text;
}

QJsonObject HtmlContent::toJsonObject() const
{
    return QJsonObject{
        { "html content", text }
    };
}
