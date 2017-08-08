#include "mediacontent.h"

MediaContent::MediaContent(const QString& source)
    : source(source)
{
    type = CONTENT_TYPE::MEDIA;
}

QJsonObject MediaContent::toJsonObject() const
{
    return {
        { "media source", source }
    };
}

QString MediaContent::getSource() const
{
    return source;
}

void MediaContent::setSource(const QString& value)
{
    source = value;
}
