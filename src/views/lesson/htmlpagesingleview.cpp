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

    setHtml(htmlPage->getContent());
}

void HtmlPageSingleView::setHtml(const QString& html)
{
    ui->content->setHtml(html);
}
