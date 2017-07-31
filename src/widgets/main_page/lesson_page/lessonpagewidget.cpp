#include "lessonpagewidget.h"

LessonPageWidget::LessonPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<LessonPageWidgetUi>(this);
}

void LessonPageWidget::activate(std::shared_ptr<Lesson> lesson)
{
    if (!lesson)
        return;

    this->lesson = lesson;
    ui->pagination->setLesson(lesson);
    if (!lesson->getPages().empty())

        ui->pageWidget->setPage(lesson->getPages().begin()->second);
}
