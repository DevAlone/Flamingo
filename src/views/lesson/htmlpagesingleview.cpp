#include "htmlpagesingleview.h"

HtmlPageSingleView::HtmlPageSingleView(QWidget* parent)
    : TextPageSingleView(parent)
{
}

void HtmlPageSingleView::setHtmlPage(std::shared_ptr<HtmlPage> htmlPage)
{
    if (!htmlPage)
        return;

    this->htmlPage = htmlPage;
    TextPageSingleView::setPage(htmlPage);

    setHtml(htmlPage->getContent());
}

void HtmlPageSingleView::setHtml(const QString& html)
{
    ui->content->setHtml(html);
}

void HtmlPageSingleView::setPage(std::shared_ptr<Page> page)
{
    auto htmlPage = std::dynamic_pointer_cast<HtmlPage>(page);
    if (!htmlPage)
        return;

    setHtmlPage(htmlPage);
}
