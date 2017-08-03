#include "checkanswerlabel.h"

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
}
