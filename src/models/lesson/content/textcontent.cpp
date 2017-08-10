#include "textcontent.h"

TextContent::TextContent(const QString& text)
    : text(text)
{
    type = CONTENT_TYPE::TEXT;
}

const QString& TextContent::getText() const
{
    return text;
}

void TextContent::setText(const QString& value)
{
    text = value;
}

QJsonObject TextContent::toJsonObject() const
{
    return QJsonObject{
        { "text content", text }
    };
}
