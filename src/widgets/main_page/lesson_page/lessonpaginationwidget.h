#ifndef LESSONPAGINATIONWIDGET_H
#define LESSONPAGINATIONWIDGET_H

#include <QtWidgets>

#include <memory>

#include <models/lesson/lesson.h>

class LessonPaginationWidgetUi;
class PageButton;

// TODO: add handling of many count of pages
class LessonPaginationWidget : public QWidget {
    Q_OBJECT
public:
    explicit LessonPaginationWidget(QWidget* parent = nullptr);

    void markPageAsActive(unsigned pageNumber);
signals:
    void goToPage(unsigned pageNumber);

public slots:
    void setLesson(std::shared_ptr<Lesson> lesson);
    void updateItems();

private slots:
    void pageButtonClicked();

private:
    std::unique_ptr<LessonPaginationWidgetUi> ui;
    std::shared_ptr<Lesson> lesson;
    std::map<unsigned, std::shared_ptr<Page>> pages;
    std::map<unsigned, PageButton*> pageButtons;
    PageButton* activePageButton;
};

class LessonPaginationWidgetUi {
    friend class LessonPaginationWidget;

public:
    LessonPaginationWidgetUi(LessonPaginationWidget* parent)
    {
        mainLayout = new QHBoxLayout;
        pageWidgetsLayout = new QHBoxLayout;

        mainLayout->addStretch();
        mainLayout->addLayout(pageWidgetsLayout);
        mainLayout->addStretch();

        parent->setLayout(mainLayout);
    }

private:
    QHBoxLayout* mainLayout;

    QHBoxLayout* pageWidgetsLayout;
};

class PageButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(bool isActive READ isActive WRITE setActiveState)
public:
    PageButton(unsigned pageNumber, const QString& text, QWidget* parent)
        : QPushButton(text, parent)
        , pageNumber(pageNumber)

    {
    }
    unsigned getPageNumber() const
    {
        return pageNumber;
    }
    bool isActive() const { return _isActive; }
    void setActiveState(bool value) { _isActive = value; }

private:
    unsigned pageNumber;
    bool _isActive = false;
};

#endif // LESSONPAGINATIONWIDGET_H
