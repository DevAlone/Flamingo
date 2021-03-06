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


#ifndef TEXTCONTENT_H
#define TEXTCONTENT_H

#include "content.h"

class TextContent : public Content {
public:
    TextContent(const QString& text = "");

    const QString& getText() const;
    void setText(const QString& value);

    QJsonObject toJsonObject() const;

protected:
    QString text = "";
};

#endif // TEXTCONTENT_H
