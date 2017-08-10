#include "audiocontent.h"

AudioContent::AudioContent(const QString& source)
    : MediaContent(source)
{
    type = CONTENT_TYPE::AUDIO;
}

QJsonObject AudioContent::toJsonObject() const
{
    return {
        { "audio source", source }
    };
}
