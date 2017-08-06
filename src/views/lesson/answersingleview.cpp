#include "answersingleview.h"

#include "answerheaderwidget.h"
#include "helper.h"

#include <QtCore>
#include <QtWidgets>

#include <models/lesson/htmlanswer.h>
#include <models/lesson/imageanswer.h>
#include <models/lesson/textanswer.h>

#include <views/lesson/content_view/contentview.h>

AnswerSingleView::AnswerSingleView(QWidget* parent)
    : QFrame(parent)
{
    ui = std::make_unique<AnswerSingleViewUi>(this);
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Raised);
    //TODO:    setFrameShadow(QFrame::Sunken);
}

AnswerSingleView* AnswerSingleView::makeAnswerView(
    QChar letter, std::shared_ptr<Answer> answer)
{
    AnswerSingleView* result = new AnswerSingleView;

    result->setAnswer(letter, answer);

    return result;
}

void AnswerSingleView::setAnswer(QChar letter, std::shared_ptr<Answer> answerPtr)
{
    this->letter = letter;
    answer = answerPtr;

    switch (answer->getType()) {
    case ANSWER_TYPE::TEXT: {
        auto textAnswer = std::dynamic_pointer_cast<TextAnswer>(answer);
        if (!textAnswer)
            throw Exception(
                QObject::tr("Unable to cast Answer to TextAnswer"));

        auto contentView = new ContentView;

        contentView->setText(textAnswer->getContent());

        setAnswerWidget(contentView);
    } break;
    case ANSWER_TYPE::HTML: {
        auto htmlAnswer = std::dynamic_pointer_cast<HtmlAnswer>(answer);
        if (!htmlAnswer)
            throw Exception(
                QObject::tr("Unable to cast Answer to HtmlAnswer"));

        auto contentView = new ContentView;

        contentView->setHtml(htmlAnswer->getContent());

        setAnswerWidget(contentView);
    } break;
    case ANSWER_TYPE::IMAGE: {
        auto imageAnswer = std::dynamic_pointer_cast<ImageAnswer>(answer);
        if (!imageAnswer)
            throw Exception(
                QObject::tr("Unable to cast Answer to ImageAnswer"));

        auto contentView = new ContentView;

        contentView->setImageFile(imageAnswer->getSource());

        setAnswerWidget(contentView);
    } break;
    default:
        throw Exception(QObject::tr("Unknown answer type"));
        break;
    }
}

std::shared_ptr<Answer> AnswerSingleView::getAnswer() const
{
    return answer;
}

QChar AnswerSingleView::getLetter() const
{
    return letter;
}

void AnswerSingleView::setLetter(const QChar& value)
{
    letter = value;
}

void AnswerSingleView::updateData()
{
    clearLayout(ui->mainLayout);

    auto answerHeader = new AnswerHeaderWidget(QString(letter));

    ui->mainLayout->addWidget(answerHeader);
    connect(
        answerHeader, &AnswerHeaderWidget::stateChanged,
        this, &AnswerSingleView::setChecked);

    if (answerWidget) {
        ui->mainLayout->addWidget(answerWidget);
        ui->mainLayout->setAlignment(answerWidget, Qt::AlignHCenter);
    }
}

void AnswerSingleView::setAnswerWidget(QWidget* answerWidget)
{
    this->answerWidget = answerWidget;
    updateData();
}

bool AnswerSingleView::isChecked() const
{
    return _isChecked;
}

void AnswerSingleView::setChecked(bool isChecked)
{
    // TODO: emit signal?
    _isChecked = isChecked;
    style()->unpolish(this);
    style()->polish(this);
    update();
    AnswerHeaderWidget* answerHeader = findChild<AnswerHeaderWidget*>();
    if (answerHeader) {
        answerHeader->updateStyle();
    }
}
