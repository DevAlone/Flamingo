#ifndef TEXTCONTENT_H
#define TEXTCONTENT_H

#include "content.h"

class TextContent : public Content {
public:
    TextContent(const QString& text = "");
    virtual QJsonObject toJsonObject() const;

    QString getText() const;
    void setText(const QString& value);

protected:
    QString text = "";
};

#endif // TEXTCONTENT_H
