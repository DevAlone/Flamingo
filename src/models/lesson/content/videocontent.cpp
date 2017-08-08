#include "videocontent.h"

VideoContent::VideoContent(const QString& source)
    : MediaContent(source)
//    , type(CONTENT_TYPE::VIDEO)
{
    type = CONTENT_TYPE::VIDEO;
}

QJsonObject VideoContent::toJsonObject() const
{
    return {
        { "video source", source }
    };
}
