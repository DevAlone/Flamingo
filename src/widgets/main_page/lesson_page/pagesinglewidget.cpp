#include "pagesinglewidget.h"
#include "views/lesson/htmlpagesingleview.h"
#include "views/lesson/textpagesingleview.h"

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

    ui->checkAnswerLabel->setText(text);
    ui->checkAnswerLabel->setCompleteness(page->getCompleteness());
    ui->checkAnswerLabel->show();

    // scroll down
    // острожно, костыль!
    QTimer::singleShot(250, [=] {
        verticalScrollBar()->setValue(verticalScrollBar()->maximum());
    });
}
