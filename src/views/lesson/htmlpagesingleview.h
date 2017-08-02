#ifndef HTMLPAGESINGLEVIEW_H
#define HTMLPAGESINGLEVIEW_H

#include "textpagesingleview.h"

#include <QWidget>

#include <models/lesson/htmlpage.h>

class HtmlPageSingleView : public TextPageSingleView {
    Q_OBJECT
public:
    explicit HtmlPageSingleView(QWidget* parent = nullptr);

    void setHtml(const QString& html);

signals:

public slots:
    void setPage(std::shared_ptr<Page> page);

    void setHtmlPage(std::shared_ptr<HtmlPage> htmlPage);

private:
    std::shared_ptr<HtmlPage> htmlPage;
};

#endif // HTMLPAGESINGLEVIEW_H
