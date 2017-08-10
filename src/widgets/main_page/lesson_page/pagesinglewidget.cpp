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


#include "pagesinglewidget.h"

#include "models/lesson/page.h"

#include <models/lesson/htmlpage.h>

#include "helper.h"

PageSingleWidget::PageSingleWidget(QWidget* parent)
    : QScrollArea(parent)
{
    ui = std::make_unique<PageSingleWidgetUi>(this);
}

void PageSingleWidget::setPage(std::shared_ptr<Page> page)
{
    if (!page)
        return;
    this->page = page;
    updateItems();
}

void PageSingleWidget::updateItems()
{
    if (!page)
        return;

    ui.reset();

    ui = std::make_unique<PageSingleWidgetUi>(this, page, page->getAnswers());
}

void PageSingleWidget::checkAnswerButtonPressed()
{
    emit checkAnswers(ui->answers->getSelectedAnswers());
}

void PageSingleWidget::handleUserAnswer(bool isAnswerRight)
{
    if (isAnswerRight)
        delete ui->checkButton;

    QString text = isAnswerRight ? tr("Excellent") : tr("Bad");
    if (!isAnswerRight) {
        text += "\n" + tr("Right answer is: ") + page->getRightAnswers().toHumanString();
    }

    ui->checkAnswerLabel->updateStyle();
    ui->checkAnswerLabel->setText(text);
    ui->checkAnswerLabel->setCompleteness(page->getCompleteness());
    ui->checkAnswerLabel->show();

    // scroll down
    // острожно, костыль!
    QTimer::singleShot(250, [=] {
        verticalScrollBar()->setValue(verticalScrollBar()->maximum());
    });
}

void PageSingleWidget::deactivate()
{
    // Острожно, костыли!
    ui.reset();
    ui = std::make_unique<PageSingleWidgetUi>(this);
}
