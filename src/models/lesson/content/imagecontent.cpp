#include "imagecontent.h"

ImageContent::ImageContent(const QString& source)
    : MediaContent(source)
{
    type = CONTENT_TYPE::IMAGE;
}

QJsonObject ImageContent::toJsonObject() const
{
    return {
        { "image source", source }
    };
}
