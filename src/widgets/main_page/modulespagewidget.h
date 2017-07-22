#ifndef MODULESPAGEWIDGET_H
#define MODULESPAGEWIDGET_H

#include <QtWidgets>

#include <models/course.h>

#include <memory>

class ModulesPageWidgetUi;

class ModulesPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit ModulesPageWidget(QWidget* parent = nullptr);

signals:

public slots:
    void activate(std::shared_ptr<Course> course);

private:
    std::unique_ptr<ModulesPageWidgetUi> ui;
};

class ModulesPageWidgetUi {
    friend class ModulesPageWidget;

public:
    ModulesPageWidgetUi(ModulesPageWidget* parent)
    {
        mainLayout = new QHBoxLayout;

        mainLayout->addWidget(new QLabel("test label 1", parent));
        mainLayout->addWidget(new QLabel("test label 2", parent));

        parent->setLayout(mainLayout);
    }

private:
    QHBoxLayout* mainLayout;

    //    ModuleListView* moduleList;
    //    ModuleSingleView* moduleView;
};

#endif // MODULESPAGEWIDGET_H
