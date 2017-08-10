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


#include "answerswidget.h"

#include <exceptions/exception.h>

#include "helper.h"

#include <models/lesson/htmlanswer.h>
#include <models/lesson/textanswer.h>

AnswersWidget::AnswersWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<AnswersWidgetUi>(this);
}

std::set<QChar> AnswersWidget::getSelectedAnswers()
{
    std::set<QChar> result;
    for (AnswerSingleView* answerView : answerViews) {
        if (answerView->isChecked())
            result.insert(answerView->getLetter());
    }
    return result;
}

void AnswersWidget::setAnswers(
    std::map<QChar, std::shared_ptr<Answer> > answers)
{
    this->answers = answers;
    updateItems();
}

void AnswersWidget::updateItems()
{
    answerViews.clear();
    ui->mainLayout->clear();

    for (auto& keyValue : answers) {
        auto answerView = AnswerSingleView::makeAnswerView(
            keyValue.first, keyValue.second);

        answerViews.push_back(answerView);
        ui->mainLayout->addAnswer(answerView);
    }
}
