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
