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
