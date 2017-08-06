#include "answerswidget.h"

#include <exceptions/exception.h>

#include "helper.h"

#include <models/lesson/htmlanswer.h>
#include <models/lesson/textanswer.h>

AnswersWidget::AnswersWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<AnswersWidgetUi>(this);
}

std::set<QChar> AnswersWidget::getSelectedAnswers()
{
    std::set<QChar> result;
    for (AnswerSingleView* answerView : answerViews) {
        if (answerView->isChecked())
            result.insert(answerView->getLetter());
    }
    return result;
}

void AnswersWidget::setAnswers(
    std::map<QChar, std::shared_ptr<Answer> > answers)
{
    this->answers = answers;
    updateItems();
}

void AnswersWidget::updateItems()
{
    answerViews.clear();
    ui->mainLayout->clear();

    for (auto& keyValue : answers) {
        auto answerView = AnswerSingleView::makeAnswerView(
            keyValue.first, keyValue.second);

        answerViews.push_back(answerView);
        ui->mainLayout->addAnswer(answerView);
    }
}
