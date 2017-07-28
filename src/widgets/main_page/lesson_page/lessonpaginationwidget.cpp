#include "lessonpaginationwidget.h"

LessonPaginationWidget::LessonPaginationWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<LessonPaginationWidgetUi>(this);
}

void LessonPaginationWidget::setLesson(std::shared_ptr<Lesson> lesson)
{
    if (!lesson)
        return;

    this->lesson = lesson;
    updateItems();
}

void clearLayout(QLayout* layout)
{
    QLayoutItem* item;
    while (item = layout->takeAt(0)) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }

        delete item->widget();

        delete item;
    }
}

void LessonPaginationWidget::updateItems()
{
    pages.clear();
    clearLayout(ui->pageWidgetsLayout);

    for (auto& pagePair : lesson->getPages()) {
        pages.insert(pagePair);

        PageButton* pageButton = new PageButton(
            pagePair.first,
            QString::number(pagePair.first),
            this);

        connect(
            pageButton, &PageButton::clicked,
            this, &LessonPaginationWidget::pageButtonClicked);

        ui->pageWidgetsLayout->addWidget(pageButton);
    }
}

void LessonPaginationWidget::pageButtonClicked()
{
    PageButton* button = qobject_cast<PageButton*>(sender());

    if (!button)
        return;

    unsigned pageNumber = button->getPageNumber();

    auto it = pages.find(pageNumber);

    if (it == pages.end())
        return;

    emit goToPage(it->second);
}
