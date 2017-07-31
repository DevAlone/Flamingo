#ifndef PAGESINGLEWIDGET_H
#define PAGESINGLEWIDGET_H

#include "answerswidget.h"
#include "pagesingleview.h"

#include <models/lesson/page.h>

#include <QtWidgets>

#include <memory>

class PageSingleWidgetUi;

class PageSingleWidget : public QScrollArea {
    Q_OBJECT
public:
    explicit PageSingleWidget(QWidget* parent = nullptr);

signals:

public slots:
    void setPage(std::shared_ptr<Page> page);
    void updateItems();

private:
    std::unique_ptr<PageSingleWidgetUi> ui;
    std::shared_ptr<Page> page;
};

class PageSingleWidgetUi {
    friend class PageSingleWidget;

public:
    PageSingleWidgetUi(QScrollArea* parent)
    {
        baseWidget = new QWidget;
        mainLayout = new QVBoxLayout;
        pageView = new PageSingleView;
        answers = new AnswersWidget;

        mainLayout->addWidget(pageView);
        mainLayout->addWidget(answers);

        mainLayout->addStretch();

        baseWidget->setLayout(mainLayout);

        parent->setWidget(baseWidget);
        parent->setWidgetResizable(true);
    }

private:
    QWidget* baseWidget;

    QVBoxLayout* mainLayout;

    PageSingleView* pageView;
    AnswersWidget* answers;
};

#endif // PAGESINGLEWIDGET_H
