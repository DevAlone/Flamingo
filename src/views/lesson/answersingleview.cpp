#include "answersingleview.h"

#include "answerheaderwidget.h"
#include "helper.h"

#include <QtCore>
#include <QtWidgets>

AnswerSingleView::AnswerSingleView(QWidget* parent)
    : QFrame(parent)
{
    ui = std::make_unique<AnswerSingleViewUi>(this);
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Raised);
    //TODO:    setFrameShadow(QFrame::Sunken);
}

void AnswerSingleView::setAnswer(QChar letter, std::shared_ptr<Answer> answerPtr)
{
    this->letter = letter;
    answer = answerPtr;
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

    //    auto headerLayout = new QHBoxLayout;
    auto answerHeader = new AnswerHeaderWidget(QString(letter));

    //    headerLayout->addWidget(checkBox);

    ui->mainLayout->addWidget(answerHeader);
    connect(
        answerHeader, &AnswerHeaderWidget::stateChanged,
        this, &AnswerSingleView::setChecked);

    if (answerWidget)
        ui->mainLayout->addWidget(answerWidget);
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
}
