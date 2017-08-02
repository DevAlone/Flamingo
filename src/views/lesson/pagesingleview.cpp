#include "pagesingleview.h"

PageSingleView::PageSingleView(QWidget* parent)
    : QWidget(parent)
{
}

void PageSingleView::setPage(std::shared_ptr<Page> pagePtr)
{
    page = pagePtr;
}

std::shared_ptr<Page> PageSingleView::getPage() const
{
    return page;
}
