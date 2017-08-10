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



#include "helper.h"

LessonPaginationWidget::LessonPaginationWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<LessonPaginationWidgetUi>(this);
}

void LessonPaginationWidget::markPageAsActive(unsigned pageNumber)
{
    auto it = pageButtons.find(pageNumber);
    if (it == pageButtons.end())
        return;

    if (activePageButton)
        activePageButton->setActiveState(false);

    it->second->setActiveState(true);
    activePageButton = it->second;
}

void LessonPaginationWidget::setLesson(std::shared_ptr<Lesson> lesson)
{
    if (!lesson)
        return;

    this->lesson = lesson;
    updateItems();
}

void LessonPaginationWidget::addPage(std::pair<unsigned, std::shared_ptr<Page> > pagePair)
{
    pages.insert(pagePair);

    PageButton* pageButton = new PageButton(
        pagePair,
        QString::number(pagePair.first),
        this);

    std::pair<unsigned, PageButton*> buttonPair;
    buttonPair.first = pagePair.first;
    buttonPair.second = pageButton;

    pageButtons.insert(buttonPair);

    connect(
        pageButton, &PageButton::clicked,
        this, &LessonPaginationWidget::pageButtonClicked);

    ui->pageWidgetsLayout->addWidget(pageButton);
}

void LessonPaginationWidget::updateItems()
{
    activePageButton = nullptr;
    pages.clear();
    pageButtons.clear();

    clearLayout(ui->pageWidgetsLayout);

    for (auto& pagePair : lesson->getPages()) {
        addPage(pagePair);
    }
}

void LessonPaginationWidget::pageButtonClicked()
{
    PageButton* button = qobject_cast<PageButton*>(sender());

    if (!button)
        return;

    unsigned pageNumber = button->getPageNumber();

    auto it = pages.find(pageNumber);

    if (it == pages.end())
        return;

    emit goToPage(it->first);
}
