#ifndef MIXEDPAGE_H
#define MIXEDPAGE_H

#include "page.h"

#include <memory>
#include <vector>

#include <models/lesson/content/content.h>

class MixedPage : public Page {
public:
    MixedPage(
        const std::map<QString, QString>& infoSectionMap,
        const std::vector<std::pair<QString, QString>>& infoSectionVec);

    virtual QJsonObject toJsonObject() const;

    const std::vector<std::shared_ptr<Content>>& getContents() const;

private:
    std::vector<std::shared_ptr<Content>> contents;
};

#endif // MIXEDPAGE_H
