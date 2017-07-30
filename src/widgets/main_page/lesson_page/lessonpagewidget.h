#ifndef LESSONPAGEWIDGET_H
#define LESSONPAGEWIDGET_H

#include "lessonpaginationwidget.h"

#include <QtWidgets>

#include <memory>

#include <models/lesson/lesson.h>

#include <views/lesson/pagesingleview.h>
#include <views/lesson/pagesinglewidget.h>

class LessonPageWidgetUi;

class LessonPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit LessonPageWidget(QWidget* parent = nullptr);

signals:

public slots:
    void activate(std::shared_ptr<Lesson> lesson);

private:
    std::unique_ptr<LessonPageWidgetUi> ui;
    std::shared_ptr<Lesson> lesson;
};

class LessonPageWidgetUi {
    friend class LessonPageWidget;

public:
    LessonPageWidgetUi(LessonPageWidget* parent)
    {
        mainLayout = new QVBoxLayout;
        pageWidget = new PageSingleWidget(parent);
        pagination = new LessonPaginationWidget(parent);

        mainLayout->addWidget(pageWidget);
        mainLayout->addWidget(pagination);

        parent->setLayout(mainLayout);

        QObject::connect(
            pagination, &LessonPaginationWidget::goToPage,
            pageWidget, &PageSingleWidget::setPage);
    }

private:
    QVBoxLayout* mainLayout;

    PageSingleWidget* pageWidget;
    LessonPaginationWidget* pagination;
};

#endif // LESSONPAGEWIDGET_H
