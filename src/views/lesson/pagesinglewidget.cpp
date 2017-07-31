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

    clearLayout(ui->mainLayout);

    switch (page->getType()) {
    case PAGE_TYPE::TEXT: {
        auto textPage = std::dynamic_pointer_cast<TextPage>(page);
        if (!textPage)
            throw Exception(
                QObject::tr("Unable to cast Page to TextPage"));

        auto pageView = new TextPageSingleView(this);
        pageView->setTextPage(textPage);
        ui->pageView = pageView;
    } break;
    case PAGE_TYPE::HTML: {
        auto htmlPage = std::dynamic_pointer_cast<HtmlPage>(page);
        if (!htmlPage)
            throw Exception(
                QObject::tr("Unable to cast Page to HtmlPage"));

        auto pageView = new HtmlPageSingleView(this);
        pageView->setHtmlPage(htmlPage);
        ui->pageView = pageView;
    } break;
    default:
        throw Exception(QObject::tr("Unknown page type"));
        break;
    }

    ui->answers = new AnswersWidget;

    ui->answers->setAnswers(page->getAnswers());

    ui->mainLayout->addWidget(ui->pageView);
    ui->mainLayout->addWidget(ui->answers);

    ui->mainLayout->addStretch();
}
