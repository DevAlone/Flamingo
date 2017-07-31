#include "textanswersingleview.h"

TextAnswerSingleView::TextAnswerSingleView(QWidget* parent)
    : AnswerSingleView(parent)
{
    ui = std::make_unique<TextAnswerSingleViewUi>(this);
}

void TextAnswerSingleView::setTextAnswer(QChar letter, std::shared_ptr<TextAnswer> textAnswer)
{
    if (!textAnswer)
        return; // TODO: clear layout?

    this->letter = letter;

    this->textAnswer = textAnswer;

    setText(QString(letter) + ": " + textAnswer->getContent());
}

void TextAnswerSingleView::setText(const QString& text)
{
    ui->content->setPlainText(text);
}
