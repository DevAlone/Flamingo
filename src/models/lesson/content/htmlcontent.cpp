#include "htmlcontent.h"

HtmlContent::HtmlContent(const QString& html)
    : TextContent(html)
{
    type = CONTENT_TYPE::HTML;
}

QJsonObject HtmlContent::toJsonObject() const
{
    return {
        { "html content", text }
    };
}

const QString& HtmlContent::getHtml()
{
    return text;
}
