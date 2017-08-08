#include "content.h"
#include "audiocontent.h"
#include "htmlcontent.h"
#include "imagecontent.h"
#include "textcontent.h"
#include "videocontent.h"

Content::Content()
{
}

std::shared_ptr<Content> Content::fromKeyValue(const QString& key, const QString& value)
{
    std::shared_ptr<Content> result;

    if (key == "text content")
        result = std::make_shared<TextContent>(value);
    else if (key == "html content")
        result = std::make_shared<HtmlContent>(value);
    else if (key == "image source")
        result = std::make_shared<ImageContent>(value);
    else if (key == "audio source")
        result = std::make_shared<AudioContent>(value);
    else if (key == "video source")
        result = std::make_shared<VideoContent>(value);

    return result;
}

CONTENT_TYPE Content::getType() const
{
    return type;
}
