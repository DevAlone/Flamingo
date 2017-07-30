#include "htmlpagesingleview.h"

HtmlPageSingleView::HtmlPageSingleView(QWidget* parent)
    : TextPageSingleView(parent)
{
    ui->content->setTextFormat(Qt::TextFormat::RichText);
}

void HtmlPageSingleView::setHtmlPage(std::shared_ptr<HtmlPage> htmlPage)
{
    if (!htmlPage)
        return;

    this->htmlPage = htmlPage;

    setContent(htmlPage->getContent());
}
