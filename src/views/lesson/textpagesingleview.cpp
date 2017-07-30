#include "textpagesingleview.h"

TextPageSingleView::TextPageSingleView(QWidget *parent)
    : PageSingleView (parent)
{
    ui = std::make_unique<TextPageSingleViewUi>(this);

    ui->content->setTextFormat(Qt::TextFormat::PlainText);
}

void TextPageSingleView::setTextPage(std::shared_ptr<TextPage> textPage)
{
    if(!textPage)
        return;

    this->textPage = textPage;

    setContent(textPage->getContent());
}

void TextPageSingleView::setContent(const QString &data)
{
    ui->content->setText(data);
}
