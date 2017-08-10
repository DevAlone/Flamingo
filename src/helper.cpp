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



#include <QtCore>
#include <QtWidgets>

void clearLayout(QLayout* layout)
{
    QLayoutItem* item;
    while (item = layout->takeAt(0)) {
        if (item->layout()) {
            clearLayout(item->layout());

            delete item->layout();
        }

        delete item->widget();

        delete item;
    }
}

QString languageCodeToString(const QString& _languageCode)
{
    // TODO: optimize and add all languages
    QString languageCode = _languageCode.simplified();
    if (languageCode.size() < 2 || languageCode.size() > 3)
        return languageCode;

    static const std::map<QString, QString> threeLetterLanguageMap = {
        { "rus", "Russian (Русский)" },
        { "eng", "English (English)" },
    };

    if (languageCode.size() == 3) {
        auto it = threeLetterLanguageMap.find(languageCode);
        if (it == threeLetterLanguageMap.end())
            return languageCode;
        return it->second;
    }

    for (auto& langPair : threeLetterLanguageMap) {
        if (langPair.first.mid(0, 2) == languageCode)
            return langPair.second;
    }

    return languageCode;
}
