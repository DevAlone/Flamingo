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
    void openButtonPressed();
public slots:
    void updateData();

protected:
private:
    std::unique_ptr<ModuleSingleViewUi> ui;
    std::shared_ptr<Module> module;
};

class ModuleSingleViewUi {
    friend class ModuleSingleView;

public:
    ModuleSingleViewUi(ModuleSingleView* parent)
    {
        mainLayout = new QVBoxLayout;
        topLayout = new QHBoxLayout;
        keyValueLayout = new QFormLayout;
        nameValue = new QLabel(parent);
        openButton = new QPushButton(QObject::tr("Open"), parent);

        level = new QLabel(QObject::tr("Level"), parent);
        levelValue = new QLabel(parent);

        description = new QLabel(QObject::tr("Description"), parent);
        descriptionValue = new QLabel(parent);

        topLayout->addWidget(nameValue);
        topLayout->addWidget(openButton);

        keyValueLayout->addRow(level, levelValue);
        keyValueLayout->addRow(description, descriptionValue);

        mainLayout->addLayout(topLayout);
        mainLayout->addLayout(keyValueLayout);

        parent->setLayout(mainLayout);

        mainLayout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            openButton, &QPushButton::clicked,
            parent, &ModuleSingleView::openButtonPressed);
    }

private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* topLayout;
    QFormLayout* keyValueLayout;
    QLabel* nameValue;

    QPushButton* openButton;

    QLabel* level;
    QLabel* levelValue;

    QLabel* description;
    QLabel* descriptionValue;
};

#endif // MODULESINGLEVIEW_H
