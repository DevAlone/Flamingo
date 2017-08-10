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
