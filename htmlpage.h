#ifndef HTMLPAGE_H
#define HTMLPAGE_H

#include "textpage.h"

class HtmlPage : public TextPage {
public:
    HtmlPage(std::map<QString, QString> infoSection);
};

#endif // HTMLPAGE_H
