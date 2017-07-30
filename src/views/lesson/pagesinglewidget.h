#ifndef PAGESINGLEWIDGET_H
#define PAGESINGLEWIDGET_H

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

private:
    std::unique_ptr<PageSingleWidgetUi> ui;
};

class PageSingleWidgetUi {
    friend class PageSingleWidget;

public:
    PageSingleWidgetUi(PageSingleWidget* parent)
    {
        baseWidget = new QWidget;
        mainLayout = new QVBoxLayout;
        pageView = new PageSingleView(parent);

        mainLayout->addWidget(pageView);

        baseWidget->setLayout(mainLayout);

        parent->setWidget(baseWidget);
    }

private:
    QWidget* baseWidget;

    QVBoxLayout* mainLayout;

    PageSingleView* pageView;
};

#endif // PAGESINGLEWIDGET_H
