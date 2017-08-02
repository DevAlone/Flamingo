#include "answertextbrowserwidget.h"

#include <QtWidgets>

AnswerTextBrowserWidget::AnswerTextBrowserWidget(QWidget* parent)
    : TextBrowserWidget(parent)
{
}

bool AnswerTextBrowserWidget::isChecked() const
{
    return _isChecked;
}

void AnswerTextBrowserWidget::setChecked(bool isChecked)
{
    // TODO: emit signal?
    _isChecked = isChecked;
}

void AnswerTextBrowserWidget::mousePressEvent(QMouseEvent* event)
{
    TextBrowserWidget::mousePressEvent(event);
}

void AnswerTextBrowserWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton || event->buttons() | Qt::LeftButton) {
        setChecked(!isChecked());
        style()->unpolish(this);
        style()->polish(this);
        repaint();
    }
    TextBrowserWidget::mouseReleaseEvent(event);
}
