#include "textcontent.h"

TextContent::TextContent(const QString& text)
    : text(text)
{
    type = CONTENT_TYPE::TEXT;
}

QJsonObject TextContent::toJsonObject() const
{
    QJsonObject obj{
        { "text content", text }
    };
    return obj;
}

QString TextContent::getText() const
{
    return text;
}

void TextContent::setText(const QString& value)
{
    text = value;
}
