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


#ifndef TEXTPAGE_H
#define TEXTPAGE_H

#include "page.h"

#include <QString>

#include <models/lesson/content/textcontent.h>

class TextPage : public Page {
public:
    TextPage(const std::map<QString, QString>& infoSection);

    const QString& getContent() const;

    virtual QJsonObject toJsonObject() const;

protected:
    TextContent content;
};

#endif // TEXTPAGE_H
