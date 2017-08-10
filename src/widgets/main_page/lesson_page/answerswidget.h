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


#define ANSWERSWIDGET_H

#include "answerslayout.h"

#include <QtWidgets>

#include <memory>

#include <models/lesson/answer.h>

#include <set>

class AnswersWidgetUi;

class AnswersWidget : public QWidget {
    Q_OBJECT
public:
    explicit AnswersWidget(QWidget* parent = nullptr);

    std::set<QChar> getSelectedAnswers();
signals:

public slots:
    void setAnswers(std::map<QChar, std::shared_ptr<Answer>> answers);
    void updateItems();

private:
    std::unique_ptr<AnswersWidgetUi> ui;
    std::map<QChar, std::shared_ptr<Answer>> answers;
    std::vector<AnswerSingleView*> answerViews;
};

class AnswersWidgetUi {
    friend class AnswersWidget;

public:
    AnswersWidgetUi(AnswersWidget* parent)
    {
        mainLayout = new AnswersLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);

        parent->setLayout(mainLayout);
    }

private:
    AnswersLayout* mainLayout;
};

#endif // ANSWERSWIDGET_H
