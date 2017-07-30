#ifndef HTMLPAGESINGLEVIEW_H
#define HTMLPAGESINGLEVIEW_H

#include "textpagesingleview.h"

#include <QWidget>

#include <models/lesson/htmlpage.h>

class HtmlPageSingleView : public TextPageSingleView
{
    Q_OBJECT
public:
    explicit HtmlPageSingleView(QWidget *parent = nullptr);

    void setTextPage(std::shared_ptr<TextPage> textPage) = delete;
    void setHtmlPage(std::shared_ptr<HtmlPage> htmlPage);

signals:

public slots:

private:
    std::shared_ptr<HtmlPage> htmlPage;
};

#endif // HTMLPAGESINGLEVIEW_H
