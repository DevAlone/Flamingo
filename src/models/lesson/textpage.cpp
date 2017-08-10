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



#include <exceptions/modelserializationerror.h>

#include <QDebug>

TextPage::TextPage(const std::map<QString, QString>& infoSection)
{
    auto contentIt = infoSection.find("content");
    if (contentIt != infoSection.end()) {

        content.setText(contentIt->second);
    }
}

const QString& TextPage::getContent() const
{
    return content.getText();
}

QJsonObject TextPage::toJsonObject() const
{
    QJsonObject obj = Page::toJsonObject();

    QJsonArray jsonInfoSection;
    if (obj["info_section"].isArray()) {
        jsonInfoSection = obj["info_section"].toArray();
    } else
        throw ModelSerializationError(
            QObject::tr("error during serialization TextPage: "
                        "info_section wasn't found"));

    jsonInfoSection.push_back(QJsonObject{
        { "content", content.getText() } });

    obj["info_section"] = jsonInfoSection;

    return obj;
}
