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


#define PAGESINGLEWIDGET_H

#include "answerswidget.h"
#include "checkanswerlabel.h"

#include <models/lesson/page.h>

#include <QtWidgets>

#include <memory>

#include <views/lesson/pagesingleview.h>

class PageSingleWidgetUi;

class PageSingleWidget : public QScrollArea {
    Q_OBJECT

    friend class PageSingleWidgetUi;

public:
    explicit PageSingleWidget(QWidget* parent = nullptr);

signals:
    void goToNextPage();
    void checkAnswers(std::set<QChar> answers);
public slots:
    void setPage(std::shared_ptr<Page> page);
    void updateItems();
    void handleUserAnswer(bool isAnswerRight);

    void deactivate();

private slots:
    void checkAnswerButtonPressed();

private:
    std::unique_ptr<PageSingleWidgetUi> ui;
    std::shared_ptr<Page> page;
};

class PageSingleWidgetUi {
    friend class PageSingleWidget;

public:
    PageSingleWidgetUi(
        PageSingleWidget* parent)
        : PageSingleWidgetUi(
              parent,
              std::shared_ptr<Page>(),
              std::map<QChar, std::shared_ptr<Answer>>())
    {
    }

    PageSingleWidgetUi(
        PageSingleWidget* parent,
        std::shared_ptr<Page> page,
        std::map<QChar, std::shared_ptr<Answer>> answerList)
    {
        baseWidget = new QWidget;
        mainLayout = new QVBoxLayout;
        checkAnswerLabel = new CheckAnswerLabel(0, "", parent);

        if (page) {
            pageView = PageSingleView::makePageView(page);

            mainLayout->addWidget(pageView);
        }

        if (!answerList.empty()) {
            answers = new AnswersWidget;

            answers->setAnswers(answerList);

            mainLayout->addWidget(answers);
        }

        mainLayout->addStretch();

        if (!answerList.empty()) {
            checkButton = new QPushButton;
            checkButton->setObjectName("checkAnswerButton");
            checkButton->setText(
                QObject::tr("Check answer"));
            mainLayout->addWidget(checkButton);
            QObject::connect(
                checkButton, &QPushButton::clicked,
                parent, &PageSingleWidget::checkAnswerButtonPressed);
        }

        checkAnswerLabel->hide();
        mainLayout->addWidget(checkAnswerLabel);

        baseWidget->setLayout(mainLayout);

        parent->setWidget(baseWidget);
        parent->setWidgetResizable(true);
    }

private:
    QWidget* baseWidget;

    QVBoxLayout* mainLayout;

    PageSingleView* pageView;
    AnswersWidget* answers;

    QPushButton* checkButton;

    CheckAnswerLabel* checkAnswerLabel;
};

#endif // PAGESINGLEWIDGET_H
