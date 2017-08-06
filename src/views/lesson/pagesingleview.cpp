#include "pagesingleview.h"

#include "helper.h"

#include "content_view/contentview.h"

#include <models/lesson/htmlpage.h>
#include <models/lesson/imagepage.h>
#include <models/lesson/textpage.h>

PageSingleView::PageSingleView(QWidget* parent)
    : QFrame(parent)
{
    ui = std::make_unique<PageSingleViewUi>(this);
}

PageSingleView* PageSingleView::makePageView(std::shared_ptr<Page> page)
{
    PageSingleView* result = new PageSingleView;

    result->setPage(page);

    return result;
}

void PageSingleView::setPage(std::shared_ptr<Page> pagePtr)
{
    page = pagePtr;

    clearLayout(ui->mainLayout);

    auto contentView = new ContentView;

    switch (page->getType()) {
    case PAGE_TYPE::TEXT: {
        auto textPage = std::dynamic_pointer_cast<TextPage>(page);
        if (!textPage)
            throw Exception(
                QObject::tr("Unable to cast Page to TextPage"));

        contentView->setText(textPage->getContent());
    } break;
    case PAGE_TYPE::HTML: {
        auto htmlPage = std::dynamic_pointer_cast<HtmlPage>(page);
        if (!htmlPage)
            throw Exception(
                QObject::tr("Unable to cast Page to HtmlPage"));

        contentView->setHtml(htmlPage->getContent());
    } break;
    case PAGE_TYPE::IMAGE: {
        auto imagePage = std::dynamic_pointer_cast<ImagePage>(page);
        if (!imagePage)
            throw Exception(
                QObject::tr("Unable to cast Page to ImagePage"));

        contentView->setImageFile(imagePage->getSource());

    } break;
    default:
        throw Exception(QObject::tr("Unknown page type"));
        break;
    }

    ui->mainLayout->addWidget(contentView);

    ui->mainLayout->setAlignment(contentView, Qt::AlignHCenter);
}

std::shared_ptr<Page> PageSingleView::getPage() const
{
    return page;
}
