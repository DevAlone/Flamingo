#include "htmlanswersingleview.h"

HtmlAnswerSingleView::HtmlAnswerSingleView(QWidget* parent)
    : TextAnswerSingleView(parent)
{
}

void HtmlAnswerSingleView::setHtmlAnswer(QChar letter, std::shared_ptr<HtmlAnswer> htmlAnswer)
{
    if (!htmlAnswer)
        return;

    this->letter = letter;

    this->htmlAnswer = htmlAnswer;

    setHtml(QString(letter) + ": " + htmlAnswer->getContent());
}

void HtmlAnswerSingleView::setHtml(const QString& html)
{
    ui->content->setHtml(html);
}
