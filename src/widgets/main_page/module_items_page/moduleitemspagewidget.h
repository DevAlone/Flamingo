#ifndef MODULEITEMSPAGEWIDGET_H
#define MODULEITEMSPAGEWIDGET_H

#include "models/module.h"
#include <widgets/main_page/twocolumnswidget.h>

#include <QtWidgets>

#include <memory>

#include <views/moduleitemsingleview.h>
#include <views/moduleitemtreeview.h>

#include <models/lesson/lesson.h>

class ModuleItemsPageWidgetUi;

class ModuleItemsPageWidget : public QWidget {
    Q_OBJECT

    friend class ModuleItemsPageWidgetUi;

public:
    explicit ModuleItemsPageWidget(QWidget* parent = nullptr);

signals:
    void goToLessonPage(std::shared_ptr<Lesson> lesson);
public slots:
    void activate(std::shared_ptr<Module> module);

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
