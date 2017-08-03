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
        if (currentPage.second && currentPage.second->getAnswers().empty()) {
            currentPage.second->setCompleteness(100);
            lesson->save();
        }

        QMessageBox::warning(
            this,
            tr("Congratulation!"),
            tr("You've just finished this lesson. "));

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

    if (currentPage.second && currentPage.second->getAnswers().empty()) {
        currentPage.second->setCompleteness(100);
        lesson->save();
    }

    ui->pageWidget->setPage(page);
    currentPage = pair;
    ui->pagination->markPageAsActive(pageNumber);
}

void LessonPageWidget::checkAnswer(std::set<QChar> answers)
{
    bool isAnswerRight = currentPage.second->getRightAnswers().isAnswersRight(answers);

    currentPage.second->setCompleteness(isAnswerRight ? 100 : 50);
    lesson->save();

    emit userAnswered(isAnswerRight);
}

void LessonPageWidget::nextPageButtonClicked()
{
    goToNextPage();
}
