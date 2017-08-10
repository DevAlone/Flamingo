// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
    void addPage(std::pair<unsigned, std::shared_ptr<Page>> pagePair);

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
    Q_PROPERTY(int completeness READ getCompleteness)

public:
    PageButton(
        std::pair<unsigned, std::shared_ptr<Page>> page,
        const QString& text,
        QWidget* parent)
        : QPushButton(text, parent)
        , page(page)

    {
    }
    unsigned getPageNumber() const
    {
        return page.first;
    }
    bool isActive() const { return _isActive; }
    void setActiveState(bool value)
    {
        _isActive = value;
        updateStyle();
    }

    int getCompleteness()
    {
        return page.second->getCompleteness();
    }
public slots:
    void updateStyle()
    {
        style()->unpolish(this);
        style()->polish(this);
        update();
    }

private:
    //    unsigned pageNumber;
    std::pair<unsigned, std::shared_ptr<Page>> page;
    bool _isActive = false;
};

#endif // LESSONPAGINATIONWIDGET_H
