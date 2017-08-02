#include "textpagesingleview.h"

TextPageSingleView::TextPageSingleView(QWidget* parent)
    : PageSingleView(parent)
{
    ui = std::make_unique<TextPageSingleViewUi>(this);
}

void TextPageSingleView::setTextPage(std::shared_ptr<TextPage> textPage)
{
    if (!textPage)
        return;

    this->textPage = textPage;
    setPage(textPage);

    setText(textPage->getContent());
}

void TextPageSingleView::setText(const QString& text)
{
    ui->content->setPlainText(text);
}
