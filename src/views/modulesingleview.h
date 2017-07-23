#ifndef MODULESINGLEVIEW_H
#define MODULESINGLEVIEW_H

#include "modelsingleview.h"

#include <QtWidgets>

#include <memory>

#include <models/module.h>

class ModuleSingleViewUi;

class ModuleSingleView : public ModelSingleView {
    Q_OBJECT
public:
    explicit ModuleSingleView(QWidget* parent = nullptr);

    virtual void setModel(std::shared_ptr<Model> model);
    void setModule(std::shared_ptr<Module> modulePtr);

    std::shared_ptr<Module> getModule() const;

signals:

public slots:
    void updateData();

protected:
    std::shared_ptr<Module> module;

private:
    std::unique_ptr<ModuleSingleViewUi> ui;
};

class ModuleSingleViewUi {
    friend class ModuleSingleView;

public:
    ModuleSingleViewUi(ModuleSingleView* parent)
    {
        mainLayout = new QVBoxLayout;
        topLayout = new QHBoxLayout;
        moduleNameValue = new QLabel(parent);

        topLayout->addWidget(moduleNameValue);

        mainLayout->addLayout(topLayout);

        parent->setLayout(mainLayout);
    }

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* topLayout;
    QLabel* moduleNameValue;
};

#endif // MODULESINGLEVIEW_H
