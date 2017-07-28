#include "pagesingleview.h"

PageSingleView::PageSingleView(QWidget* parent)
    : QScrollArea(parent)
{
    ui = std::make_unique<PageSingleViewUi>(this);
}

void PageSingleView::setPage(std::shared_ptr<Page> page)
{
    if (!page)
        return;

    ui->testLabel->setText(QString::number(page->getNumber()));
}
