#include "pagesingleview.h"

#include "htmlpagesingleview.h"
#include "textpagesingleview.h"

class TextPage;
class HtmlPage;

PageSingleView::PageSingleView(QWidget* parent)
    : QWidget(parent)
{
}

PageSingleView* PageSingleView::makePageView(std::shared_ptr<Page> page)
{
    PageSingleView* result;

    switch (page->getType()) {
    case PAGE_TYPE::TEXT: {
        auto textPage = std::dynamic_pointer_cast<TextPage>(page);
        if (!textPage)
            throw Exception(
                QObject::tr("Unable to cast Page to TextPage"));

        result = new TextPageSingleView;
        result->setPage(page);
    } break;
    case PAGE_TYPE::HTML: {
        auto htmlPage = std::dynamic_pointer_cast<HtmlPage>(page);
        if (!htmlPage)
            throw Exception(
                QObject::tr("Unable to cast Page to HtmlPage"));

        result = new HtmlPageSingleView;
        result->setPage(page);
    } break;
    default:
        throw Exception(QObject::tr("Unknown page type"));
        break;
    }

    return result;
}

void PageSingleView::setPage(std::shared_ptr<Page> pagePtr)
{
    page = pagePtr;
}

std::shared_ptr<Page> PageSingleView::getPage() const
{
    return page;
}
