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
    this->pages = lesson->getPages();

    ui->pagination->setLesson(lesson);
    if (!lesson->getPages().empty())
        goToPage(lesson->getPages().begin()->first);
}

void LessonPageWidget::goToNextPage()
{
    auto nextIt = pages.upper_bound(currentPage.first);
    if (nextIt == pages.end()) {
        emit lessonFinished();
        return;
    }
    goToPage(nextIt->first);
}

void LessonPageWidget::goToPage(unsigned pageNumber)
{
    auto it = pages.find(pageNumber);
    if (it == pages.end())
        return;

    auto pair = *it;

    std::shared_ptr<Page> page = pair.second;
    if (!page)
        return;
    // TODO: some checks

    ui->pageWidget->setPage(page);
    currentPage = pair;
    ui->pagination->markPageAsActive(pageNumber);
}

void LessonPageWidget::nextPageButtonClicked()
{
    goToNextPage();
}
