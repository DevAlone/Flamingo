#include "answerheaderwidget.h"

AnswerHeaderWidget::AnswerHeaderWidget(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text(text)
{
    ui = std::make_unique<AnswerHeaderWidgetUi>(this);
}

void AnswerHeaderWidget::updateStyle()
{
    style()->unpolish(this);
    style()->polish(this);
    update();
    ui->checkBox->style()->unpolish(ui->checkBox);
    ui->checkBox->style()->polish(ui->checkBox);
    ui->checkBox->update();
}

void AnswerHeaderWidget::checkBoxStateChanged()
{
    updateStyle();
    emit stateChanged(ui->checkBox->isChecked());
}

void AnswerHeaderWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton || event->buttons() | Qt::LeftButton) {
        ui->checkBox->setChecked(!ui->checkBox->isChecked());
    }
}
