#ifndef MODULEITEMSPAGEWIDGET_H
#define MODULEITEMSPAGEWIDGET_H

#include "models/module.h"
#include <widgets/main_page/twocolumnswidget.h>

#include <QtWidgets>

#include <memory>

#include <views/moduleitemsingleview.h>
#include <views/moduleitemtreeview.h>

class ModuleItemsPageWidgetUi;

class ModuleItemsPageWidget : public QWidget {
    Q_OBJECT

    friend class ModuleItemsPageWidgetUi;

public:
    explicit ModuleItemsPageWidget(QWidget* parent = nullptr);

signals:

public slots:
    void activate(std::shared_ptr<Module> module);

private slots:
    void selectedModuleItemChanged();
    void moduleItemOpenButtonPressed();

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

        QObject::connect(
            moduleItemsTree, &ModuleItemTreeView::selectionChanged,
            parent, &ModuleItemsPageWidget::selectedModuleItemChanged);

        //        QObject::connect(
        //            moduleItemView, &ModuleItemSingleView::openButtonPressed,
        //            parent, &ModuleItemsPageWidget::moduleItemOpenButtonPressed);
    }

private:
    QHBoxLayout* mainLayout;
    TwoColumnsWidget* columns;

    ModuleItemTreeView* moduleItemsTree;
    ModuleItemSingleView* moduleItemView;
};

#endif // MODULEITEMSPAGEWIDGET_H
