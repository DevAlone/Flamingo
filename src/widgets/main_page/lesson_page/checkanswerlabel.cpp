#include "checkanswerlabel.h"

#include <QStyle>

CheckAnswerLabel::CheckAnswerLabel(int completeness, const QString& text, QWidget* parent)
    : QLabel(text, parent)
    , completeness(completeness)
{
}

int CheckAnswerLabel::getCompleteness() const
{
    return completeness;
}

void CheckAnswerLabel::setCompleteness(int value)
{
    completeness = value;
    updateStyle();
}

void CheckAnswerLabel::updateStyle()
{
    style()->unpolish(this);
    style()->polish(this);
    update();
}
