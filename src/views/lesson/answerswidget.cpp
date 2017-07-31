#include "answerswidget.h"
#include "answersingleview.h"
#include "htmlanswersingleview.h"
#include "textanswersingleview.h"

#include <exceptions/exception.h>

#include "helper.h"

AnswersWidget::AnswersWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<AnswersWidgetUi>(this);
}

void AnswersWidget::setAnswers(
    std::map<QChar, std::shared_ptr<Answer> > answers)
{
    this->answers = answers;
    updateItems();
}

void AnswersWidget::updateItems()
{
    // TODO: update
    std::vector<AnswerSingleView*> answerViews;

    // add widgets to list
    for (auto& keyValue : answers) {
        const QChar& letter = keyValue.first;
        std::shared_ptr<Answer>& answer = keyValue.second;

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
    clearLayout(ui->mainLayout);

    for (auto& answerView : answerViews) {
        ui->mainLayout->addWidget(answerView);
    }
}
