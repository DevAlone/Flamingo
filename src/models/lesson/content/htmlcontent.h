#ifndef HTMLCONTENT_H
#define HTMLCONTENT_H

#include "textcontent.h"

class HtmlContent : public TextContent {
public:
    HtmlContent(const QString& html = "");

    const QString& getHtml();

    virtual QJsonObject toJsonObject() const;
};

#endif // HTMLCONTENT_H
