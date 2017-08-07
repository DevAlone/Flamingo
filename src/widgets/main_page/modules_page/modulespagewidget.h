#ifndef MODULESPAGEWIDGET_H
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
