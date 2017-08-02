#include "textanswersingleview.h"

TextAnswerSingleView::TextAnswerSingleView(QWidget* parent)
    : AnswerSingleView(parent)
{
    answerWidget = new TextAnswerSingleViewUi(this);
}

void TextAnswerSingleView::setTextAnswer(QChar letter, std::shared_ptr<TextAnswer> textAnswer)
{
    if (!textAnswer)
        return; // TODO: clear layout?

    this->letter = letter;

    this->textAnswer = textAnswer;
    setAnswer(letter, textAnswer);

    setText(QString(letter) + ": " + textAnswer->getContent());
}

void TextAnswerSingleView::setText(const QString& text)
{
    answerWidget->content->setPlainText(text);
    setAnswerWidget(answerWidget);
}
