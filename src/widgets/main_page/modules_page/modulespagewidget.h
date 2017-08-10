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


#define MODULESPAGEWIDGET_H

#include <QtWidgets>

#include <models/course.h>

#include <memory>

#include <views/modulelistview.h>
#include <views/modulesingleview.h>

#include <widgets/main_page/twocolumnswidget.h>

#include <widgets/abstractpagewidget.h>

class ModulesPageWidgetUi;

class ModulesPageWidget : public AbstractPageWidget {
    Q_OBJECT

    friend class ModulesPageWidgetUi;

public:
    explicit ModulesPageWidget(QWidget* parent = nullptr);

signals:
    void goToModuleItemsPage(std::shared_ptr<Module> module);
public slots:
    void activate();
    void setCourse(std::shared_ptr<Course> course);

private slots:
    void selectedModuleChanged();
    void moduleOpenButtonPressed();

private:
    std::unique_ptr<ModulesPageWidgetUi> ui;
    std::shared_ptr<Course> course;
};

class ModulesPageWidgetUi {
    friend class ModulesPageWidget;

public:
    ModulesPageWidgetUi(ModulesPageWidget* parent)
    {
        mainLayout = new QHBoxLayout;
        moduleList = new ModuleListView(parent);
        moduleView = new ModuleSingleView(parent);
        columns = new TwoColumnsWidget(parent);

        modulesHeader = new QLabel(
            QObject::tr("Choose module"), parent);

        mainLayout->addWidget(columns);

        columns->addLeftWidget(modulesHeader);
        columns->addLeftWidget(moduleList);

        columns->addRightWidget(moduleView);

        parent->setLayout(mainLayout);

        mainLayout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            moduleList, &ModuleListView::selectionChanged,
            parent, &ModulesPageWidget::selectedModuleChanged);

        QObject::connect(
            moduleView, &ModuleSingleView::openButtonPressed,
            parent, &ModulesPageWidget::moduleOpenButtonPressed);
    }

private:
    QHBoxLayout* mainLayout;
    TwoColumnsWidget* columns;

    ModuleListView* moduleList;
    ModuleSingleView* moduleView;

    QLabel* modulesHeader;
};

#endif // MODULESPAGEWIDGET_H
