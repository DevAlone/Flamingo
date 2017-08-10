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


#include "mixedpage.h"

#include <exceptions/modelserializationerror.h>

#include <models/lesson/content/audiocontent.h>
#include <models/lesson/content/htmlcontent.h>
#include <models/lesson/content/imagecontent.h>
#include <models/lesson/content/mediacontent.h>
#include <models/lesson/content/textcontent.h>
#include <models/lesson/content/videocontent.h>

MixedPage::MixedPage(
    const std::map<QString, QString>& infoSectionMap,
    const std::vector<std::pair<QString, QString> >& infoSectionVec)
{
    for (auto& pair : infoSectionVec) {
        auto content = Content::fromKeyValue(pair.first, pair.second);
        if (content)
            contents.push_back(content);
    }
}

QJsonObject MixedPage::toJsonObject() const
{
    QJsonObject obj = Page::toJsonObject();

    QJsonArray jsonInfoSection;
    if (obj["info_section"].isArray())
        jsonInfoSection = obj["info_section"].toArray();
    else
        throw ModelSerializationError(
            QObject::tr("error during serialization of MixedPage: "
                        "info_section wasn't found"));

    for (auto& content : contents)
        jsonInfoSection.push_back(content->toJsonObject());

    obj["info_section"] = jsonInfoSection;

    return obj;
}

const std::vector<std::shared_ptr<Content> >& MixedPage::getContents() const
{
    return contents;
}
