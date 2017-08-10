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
