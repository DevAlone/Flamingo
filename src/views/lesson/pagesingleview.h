#ifndef PAGESINGLEVIEW_H
#define PAGESINGLEVIEW_H

#include <QtWidgets>

#include <memory>

#include <models/lesson/page.h>

#include <views/modelsingleview.h>

class PageSingleViewUi;

class PageSingleView : public QFrame {
    Q_OBJECT
    explicit PageSingleView(QWidget* parent = nullptr);

public:
    static PageSingleView* makePageView(std::shared_ptr<Page> page);

    virtual void setPage(std::shared_ptr<Page> pagePtr);

    std::shared_ptr<Page> getPage() const;

signals:

public slots:

protected:
    std::shared_ptr<Page> page;

private:
    std::unique_ptr<PageSingleViewUi> ui;
};

class PageSingleViewUi {
    friend class PageSingleView;

public:
    PageSingleViewUi(PageSingleView* parent)
    {
        mainLayout = new QVBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);

        parent->setLayout(mainLayout);
    }

private:
    QVBoxLayout* mainLayout;
};

#endif // PAGESINGLEVIEW_H
