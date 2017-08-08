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
