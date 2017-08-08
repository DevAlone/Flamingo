#ifndef HTMLCONTENT_H
#define HTMLCONTENT_H

#include "textcontent.h"

class HtmlContent : public TextContent {
public:
    HtmlContent(const QString& html = "");
    virtual QJsonObject toJsonObject() const;

    const QString& getHtml();
};

#endif // HTMLCONTENT_H
