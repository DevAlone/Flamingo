#include "answerswidget.h"

#include <exceptions/exception.h>

#include "helper.h"

#include <models/lesson/htmlanswer.h>
#include <models/lesson/textanswer.h>

#include <views/lesson/htmlanswersingleview.h>
#include <views/lesson/textanswersingleview.h>

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

    // add widgets to list
    for (auto& keyValue : answers) {
        const QChar& letter = keyValue.first;
        std::shared_ptr<Answer>& answer = keyValue.second;

        // TODO: change to fabric
        switch (answer->getType()) {
        case ANSWER_TYPE::TEXT: {
            auto textAnswer
                = std::dynamic_pointer_cast<TextAnswer>(answer);
            if (!textAnswer)
                throw Exception(
                    QObject::tr("Unable to cast Answer to TextAnswer"));

            auto textAnswerView = new TextAnswerSingleView;
            textAnswerView->setTextAnswer(letter, textAnswer);
            answerViews.push_back(textAnswerView);
        } break;
        case ANSWER_TYPE::HTML: {
            auto htmlAnswer
                = std::dynamic_pointer_cast<HtmlAnswer>(answer);
            if (!htmlAnswer)
                throw Exception(
                    QObject::tr("Unable to cast Answer to HtmlAnswer"));

            auto htmlAnswerView = new HtmlAnswerSingleView;
            htmlAnswerView->setHtmlAnswer(letter, htmlAnswer);
            answerViews.push_back(htmlAnswerView);
        } break;
        default:
            throw Exception(QObject::tr("Unknown answer type"));
            break;
        }
    }

    // add from list to layout
    ui->mainLayout->clear();

    for (auto& answerView : answerViews) {
        ui->mainLayout->addAnswer(answerView);
    }
}