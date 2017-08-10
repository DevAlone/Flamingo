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
