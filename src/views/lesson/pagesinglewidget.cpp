#include "pagesinglewidget.h"
#include "htmlpagesingleview.h"
#include "textpagesingleview.h"

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
    QMessageBox::warning(this, "checking...", "checking...");
}
