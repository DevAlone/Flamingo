#include "answersingleview.h"

#include "answerheaderwidget.h"
#include "helper.h"

#include <QtCore>
#include <QtWidgets>

#include <models/lesson/audioanswer.h>
#include <models/lesson/htmlanswer.h>
#include <models/lesson/imageanswer.h>
#include <models/lesson/mixedanswer.h>
#include <models/lesson/textanswer.h>
#include <models/lesson/videoanswer.h>

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

    auto contentView = new ContentView;
    switch (answer->getType()) {
    case ANSWER_TYPE::TEXT: {
        auto textAnswer = std::static_pointer_cast<TextAnswer>(answer);

        contentView->setText(textAnswer->getContent());
    } break;
    case ANSWER_TYPE::HTML: {
        auto htmlAnswer = std::static_pointer_cast<HtmlAnswer>(answer);

        contentView->setHtml(htmlAnswer->getContent());

    } break;
    case ANSWER_TYPE::IMAGE: {
        auto imageAnswer = std::static_pointer_cast<ImageAnswer>(answer);

        contentView->setImageFile(imageAnswer->getSource());

    } break;
    case ANSWER_TYPE::AUDIO: {
        auto audioAnswer = std::static_pointer_cast<AudioAnswer>(answer);

        contentView->setAudioFile(audioAnswer->getSource());
    } break;
    case ANSWER_TYPE::VIDEO: {
        auto videoAnswer = std::static_pointer_cast<VideoAnswer>(answer);

        contentView->setVideoFile(videoAnswer->getSource());
    } break;
    case ANSWER_TYPE::MIXED: {
        auto mixedAnswer = std::static_pointer_cast<MixedAnswer>(answer);

        contentView->setContents(mixedAnswer->getContents());
    } break;
    default:
        throw Exception(QObject::tr("Unknown answer type"));
        break;
    }

    setAnswerWidget(contentView);
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
        answerWidget->setObjectName("answerWidget");
        ui->mainLayout->addWidget(answerWidget);
        ui->mainLayout->setAlignment(answerWidget, Qt::AlignHCenter);
    }

    ui->mainLayout->addStretch();
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
