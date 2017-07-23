#ifndef MODULESPAGEWIDGET_H
#define MODULESPAGEWIDGET_H

#include <QtWidgets>

#include <models/course.h>

#include <memory>

#include <views/modulelistview.h>
#include <views/modulesingleview.h>

class ModulesPageWidgetUi;

class ModulesPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit ModulesPageWidget(QWidget* parent = nullptr);

signals:

public slots:
    void activate(std::shared_ptr<Course> course);
    void selectedModuleChanged();

private slots:

private:
    std::unique_ptr<ModulesPageWidgetUi> ui;
};

class ModulesPageWidgetUi {
    friend class ModulesPageWidget;

public:
    ModulesPageWidgetUi(ModulesPageWidget* parent)
    {
        mainLayout = new QHBoxLayout;
        moduleList = new ModuleListView(parent);
        moduleView = new ModuleSingleView(parent);

        mainLayout->addWidget(moduleList);
        mainLayout->addWidget(moduleView);

        parent->setLayout(mainLayout);

        QObject::connect(
            moduleList, &ModuleListView::selectionChanged,
            parent, &ModulesPageWidget::selectedModuleChanged);
    }

private:
    QHBoxLayout* mainLayout;

    ModuleListView* moduleList;
    ModuleSingleView* moduleView;
};

#endif // MODULESPAGEWIDGET_H
