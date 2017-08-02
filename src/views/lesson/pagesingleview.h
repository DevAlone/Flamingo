#ifndef PAGESINGLEVIEW_H
#define PAGESINGLEVIEW_H

#include <QtWidgets>

#include <memory>

#include <models/lesson/page.h>

#include <views/modelsingleview.h>

class PageSingleView : public QWidget {
    Q_OBJECT
public:
    explicit PageSingleView(QWidget* parent = nullptr);

    static PageSingleView* makePageView(std::shared_ptr<Page> page);

    virtual void setModel(std::shared_ptr<Model>& model) = delete;
    virtual void setPage(std::shared_ptr<Page> pagePtr);

    std::shared_ptr<Page> getPage() const;

signals:

public slots:

protected:
    std::shared_ptr<Page> page;

private:
};

#endif // PAGESINGLEVIEW_H
