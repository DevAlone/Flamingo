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

#ifndef LESSONPAGEWIDGET_H
#define LESSONPAGEWIDGET_H

#include "lessonpaginationwidget.h"

#include <QtWidgets>

#include <memory>

#include <models/lesson/lesson.h>

#include <views/lesson/pagesingleview.h>
#include <widgets/abstractpagewidget.h>
#include <widgets/main_page/lesson_page/pagesinglewidget.h>

class LessonPageWidgetUi;

class LessonPageWidget : public AbstractPageWidget {
    Q_OBJECT

    friend class LessonPageWidgetUi;

public:
    explicit LessonPageWidget(QWidget* parent = nullptr);

signals:
    void lessonFinished();
    void userAnswered(bool isAnswerRight);

public slots:
    void setLesson(std::shared_ptr<Lesson> lesson);
    void deactivate();

    void goToNextPage();
    void goToPage(unsigned pageNumber);

    void checkAnswer(std::set<QChar> answers);

private slots:
    void nextPageButtonClicked();

private:
    std::unique_ptr<LessonPageWidgetUi> ui;
    std::shared_ptr<Lesson> lesson;
    std::map<unsigned, std::shared_ptr<Page>> pages;
    std::pair<unsigned, std::shared_ptr<Page>> currentPage;
};

class LessonPageWidgetUi {
    friend class LessonPageWidget;

public:
    LessonPageWidgetUi(LessonPageWidget* parent)
    {
        mainLayout = new QVBoxLayout;
        pageWidget = new PageSingleWidget(parent);

        bottomLayout = new QHBoxLayout;

        pagination = new LessonPaginationWidget(parent);
        nextPageButton = new QPushButton(
            QObject::tr("Next page >"));
        nextPageButton->setObjectName("nextPageButton");

        bottomLayout->addWidget(pagination);
        bottomLayout->addWidget(nextPageButton);

        mainLayout->addWidget(pageWidget);
        mainLayout->addLayout(bottomLayout);

        parent->setLayout(mainLayout);

        bottomLayout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            pagination, &LessonPaginationWidget::goToPage,
            parent, &LessonPageWidget::goToPage);

        QObject::connect(
            pageWidget, &PageSingleWidget::goToNextPage,
            parent, &LessonPageWidget::goToNextPage);

        QObject::connect(
            nextPageButton, &QPushButton::clicked,
            parent, &LessonPageWidget::nextPageButtonClicked);

        QObject::connect(
            pageWidget, &PageSingleWidget::checkAnswers,
            parent, &LessonPageWidget::checkAnswer);

        QObject::connect(
            parent, &LessonPageWidget::userAnswered,
            pageWidget, &PageSingleWidget::handleUserAnswer);
    }

private:
    QVBoxLayout* mainLayout;

    PageSingleWidget* pageWidget;

    QHBoxLayout* bottomLayout;

    LessonPaginationWidget* pagination;

    QPushButton* nextPageButton;
};

#endif // LESSONPAGEWIDGET_H
