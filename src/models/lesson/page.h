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


#define PAGE_H

#include "answer.h"
#include "rightanswers.h"

#include <QObject>
#include <QString>

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include <exceptions/pagecreatingerror.h>

enum class PAGE_TYPE : int {
    TEXT,
    HTML,
    IMAGE,
    AUDIO,
    VIDEO,
    MIXED
};

const std::map<QString, PAGE_TYPE> pageTypesMap = {
    { "text", PAGE_TYPE::TEXT },
    { "html", PAGE_TYPE::HTML },
    { "image", PAGE_TYPE::IMAGE },
    { "audio", PAGE_TYPE::AUDIO },
    { "video", PAGE_TYPE::VIDEO },
    { "mixed", PAGE_TYPE::MIXED },
};

class Page {

public:
    Page() {}
    virtual ~Page() {}

    // Fabric method which creates page
    // method automatically detect type
    // and creates appropriate class from hierarchy.
    // If one of necessary keys is missing,
    // method can throw exception
    static std::shared_ptr<Page> createPage(
        unsigned pageNumber,
        std::map<QString, QString>& infoSectionMap,
        std::vector<std::pair<QString, QString>>& infoSectionVec,
        std::map<QChar, std::shared_ptr<Answer>>& answers);

    unsigned getNumber() const;

    PAGE_TYPE getType() const;

    const std::map<QChar, std::shared_ptr<Answer>>& getAnswers() const;

    virtual QJsonObject toJsonObject() const;
    static std::shared_ptr<Page> fromJsonObject(const QJsonObject& obj);

    const RightAnswers& getRightAnswers() const;

    unsigned char getCompleteness() const;
    void setCompleteness(unsigned char value);

protected:
    unsigned number = 0;
    PAGE_TYPE type;
    std::map<QChar, std::shared_ptr<Answer>> answers;
    //    QString rightAnswers;
    RightAnswers rightAnswers;
    // value from 0 to 100
    unsigned char completeness = 0;
};

#endif // PAGE_H
