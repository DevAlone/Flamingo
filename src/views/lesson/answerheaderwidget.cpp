#include "answerheaderwidget.h"

AnswerHeaderWidget::AnswerHeaderWidget(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text(text)
{
    ui = std::make_unique<AnswerHeaderWidgetUi>(this);
}

void AnswerHeaderWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton || event->buttons() | Qt::LeftButton) {
        ui->checkBox->setChecked(!ui->checkBox->isChecked());
    }
}
