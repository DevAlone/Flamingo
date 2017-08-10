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


#ifndef MODULEITEMSPAGEWIDGET_H
#define MODULEITEMSPAGEWIDGET_H

#include "models/module.h"
#include <widgets/main_page/twocolumnswidget.h>

#include <QtWidgets>

#include <memory>

#include <views/moduleitemsingleview.h>
#include <views/moduleitemtreeview.h>

#include <models/lesson/lesson.h>

#include <widgets/abstractpagewidget.h>

class ModuleItemsPageWidgetUi;

class ModuleItemsPageWidget : public AbstractPageWidget {
    Q_OBJECT

    friend class ModuleItemsPageWidgetUi;

public:
    explicit ModuleItemsPageWidget(QWidget* parent = nullptr);

signals:
    void goToLessonPage(std::shared_ptr<Lesson> lesson);
public slots:
    void activate();
    void setModule(std::shared_ptr<Module> module);

private slots:
    void selectedModuleItemChanged();
    void lessonStartButtonPressed();

private:
    std::unique_ptr<ModuleItemsPageWidgetUi> ui;
    std::shared_ptr<Module> module;
};

class ModuleItemsPageWidgetUi {
    friend class ModuleItemsPageWidget;

public:
    ModuleItemsPageWidgetUi(ModuleItemsPageWidget* parent)
    {
        mainLayout = new QHBoxLayout;
        columns = new TwoColumnsWidget(parent);
        moduleItemsTree = new ModuleItemTreeView(parent);
        moduleItemView = new ModuleItemSingleView(parent);

        columns->addLeftWidget(moduleItemsTree);
        columns->addRightWidget(moduleItemView);

        mainLayout->addWidget(columns);

        parent->setLayout(mainLayout);

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        QObject::connect(
            moduleItemsTree, &ModuleItemTreeView::selectionChanged,
            parent, &ModuleItemsPageWidget::selectedModuleItemChanged);

        QObject::connect(
            moduleItemView, &ModuleItemSingleView::lessonStartButtonPressed,
            parent, &ModuleItemsPageWidget::lessonStartButtonPressed);
    }

private:
    QHBoxLayout* mainLayout;
    TwoColumnsWidget* columns;

    ModuleItemTreeView* moduleItemsTree;
    ModuleItemSingleView* moduleItemView;
};

#endif // MODULEITEMSPAGEWIDGET_H
