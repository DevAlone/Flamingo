#include "textpagesingleview.h"

TextPageSingleView::TextPageSingleView(QWidget* parent)
    : PageSingleView(parent)
{
    ui = std::make_unique<TextPageSingleViewUi>(this);
}

void TextPageSingleView::setPage(std::shared_ptr<Page> page)
{
    auto textPage = std::dynamic_pointer_cast<TextPage>(page);
    if (!textPage)
        return;

    setTextPage(textPage);
}

void TextPageSingleView::setTextPage(std::shared_ptr<TextPage> textPage)
{
    if (!textPage)
        return;

    this->textPage = textPage;
    PageSingleView::setPage(textPage);

    setText(textPage->getContent());
}

void TextPageSingleView::setText(const QString& text)
{
    ui->content->setPlainText(text);
}
