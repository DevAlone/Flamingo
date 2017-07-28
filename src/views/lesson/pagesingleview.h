#ifndef PAGESINGLEVIEW_H
#define PAGESINGLEVIEW_H

#include <QtWidgets>

#include <memory>

#include <models/lesson/page.h>

class PageSingleViewUi;

class PageSingleView : public QScrollArea {
    Q_OBJECT
public:
    explicit PageSingleView(QWidget* parent = nullptr);

signals:

public slots:
    void setPage(std::shared_ptr<Page> page);

private:
    std::unique_ptr<PageSingleViewUi> ui;
};

class PageSingleViewUi {
    friend class PageSingleView;

public:
    PageSingleViewUi(PageSingleView* parent)
    {
        baseWidget = new QWidget;

        mainLayout = new QVBoxLayout;

        testLabel = new QLabel;

        mainLayout->addWidget(testLabel);
        mainLayout->addWidget(new QLabel("test"));

        baseWidget->setLayout(mainLayout);

        parent->setWidget(baseWidget);
    }

private:
    QWidget* baseWidget;

    QVBoxLayout* mainLayout;

    QLabel* testLabel;
};

#endif // PAGESINGLEVIEW_H
