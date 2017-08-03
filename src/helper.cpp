#include "helper.h"

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
