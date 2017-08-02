#include "answerslayout.h"

#include "helper.h"

AnswersLayout::AnswersLayout(QWidget* parent)
    : QVBoxLayout(parent)
{
}

void AnswersLayout::addAnswer(AnswerSingleView* answerView)
{
    if (!horizontalLayout) {
        horizontalLayout = new QHBoxLayout;
        addLayout(horizontalLayout);
    }

    if (horizontalLayout->count() < 2) {
        horizontalLayout->addWidget(answerView);

    } else {
        horizontalLayout = new QHBoxLayout;
        addLayout(horizontalLayout);
        horizontalLayout->addWidget(answerView);
    }
}

void AnswersLayout::clear()
{
    clearLayout(this);
    horizontalLayout = nullptr;
}
