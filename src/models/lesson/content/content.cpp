// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "content.h"
#include "audiocontent.h"
#include "htmlcontent.h"
#include "imagecontent.h"
#include "textcontent.h"
#include "videocontent.h"

#include <exceptions/exception.h>

Content::Content()
{
}

CONTENT_TYPE Content::getType() const
{
    return type;
}

std::shared_ptr<Content> Content::fromKeyValue(
    const QString& key,
    const QString& value)
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

QJsonObject Content::toJsonObject() const
{
    throw Exception("Not implemented");
}
