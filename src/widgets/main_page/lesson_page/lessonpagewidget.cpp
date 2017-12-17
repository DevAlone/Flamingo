// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "lessonpagewidget.h"

LessonPageWidget::LessonPageWidget(QWidget* parent)
    : AbstractPageWidget(parent)
{
    ui = std::make_unique<LessonPageWidgetUi>(this);
}

void LessonPageWidget::setLesson(std::shared_ptr<Lesson> lesson)
{
    this->lesson = lesson;
    this->pages = lesson->getPages();

    ui->pagination->setLesson(lesson);
    if (!lesson->getPages().empty())
        goToPage(lesson->getPages().begin()->first);
}

void LessonPageWidget::deactivate()
{
    ui->pageWidget->deactivate();
}

void LessonPageWidget::goToNextPage()
{
    auto nextIt = pages.upper_bound(currentPage.first);
    if (nextIt == pages.end()) {
        if (currentPage.second && currentPage.second->getAnswers().empty()) {
            currentPage.second->setCompleteness(100);
            lesson->save();
        }

        //        ui->pageWidget->deactivate();

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

    if (isAnswerRight) {
        unsigned savedPageNumber = currentPage.first;
        QSettings s;
        int interval = s.value("interface/lesson/pageAutoSwitchTime", 1000).toInt();
        if (interval < 0)
            return;
        QTimer::singleShot(interval, [=] {
            if (savedPageNumber == currentPage.first)
                goToNextPage();
        });
    }
}

void LessonPageWidget::nextPageButtonClicked()
{
    goToNextPage();
}
