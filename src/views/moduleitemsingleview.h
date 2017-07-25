#ifndef MODULEITEMSINGLEVIEW_H
#define MODULEITEMSINGLEVIEW_H

#include "models/moduleitem.h"

#include <QtWidgets>

#include <views/modelsingleview.h>

#include <memory>

class ModuleItemSingleViewUi;

class ModuleItemSingleView : public ModelSingleView {
    Q_OBJECT
    friend class ModuleItemSingleViewUi;

public:
    explicit ModuleItemSingleView(QWidget* parent = nullptr);

    virtual void setModel(std::shared_ptr<Model> model);
    void setModuleItem(std::shared_ptr<ModuleItem> moduleItemPtr);

    std::shared_ptr<ModuleItem> getModuleItem() const;

signals:

public slots:
    void updateData();

private:
    std::unique_ptr<ModuleItemSingleViewUi> ui;
    std::shared_ptr<ModuleItem> moduleItem;
};

class ModuleItemSingleViewUi {
    friend class ModuleItemSingleView;

public:
    ModuleItemSingleViewUi(ModuleItemSingleView* parent)
    {
        mainLayout = new QHBoxLayout;

        submoduleWidget = new QWidget(parent);
        lessonWidget = new QWidget(parent);

        submoduleLayout = new QVBoxLayout;
        lessonLayout = new QVBoxLayout;

        submoduleWidget->setLayout(submoduleLayout);
        lessonWidget->setLayout(lessonLayout);

        makeSubmodulesWidgets(parent);
        makeLessonsWidgets(parent);

        mainLayout->addWidget(submoduleWidget);
        mainLayout->addWidget(lessonWidget);

        showSubmodule();

        parent->setLayout(mainLayout);
    }
    void showSubmodule()
    {
        lessonWidget->hide();
        submoduleWidget->show();
    }

    void showLesson()
    {
        submoduleWidget->hide();
        lessonWidget->show();
    }

private:
    QHBoxLayout* mainLayout;

    QWidget* submoduleWidget;
    QWidget* lessonWidget;

    QVBoxLayout* submoduleLayout;
    QVBoxLayout* lessonLayout;
    QFormLayout* lessonKeyValueLayout;

    QLabel* submoduleNameValue;

    QLabel* lessonNameValue;
    QLabel* lessonPagesCount;
    QLabel* lessonPagesCountValue;

    QPushButton* lessonStartButton;

    void makeSubmodulesWidgets(ModuleItemSingleView* parent)
    {
        submoduleNameValue = new QLabel(parent);

        submoduleLayout->addWidget(submoduleNameValue);
        submoduleLayout->addStretch();
    }
    void makeLessonsWidgets(ModuleItemSingleView* parent)
    {
        lessonKeyValueLayout = new QFormLayout;

        lessonNameValue = new QLabel(parent);
        lessonPagesCount = new QLabel(parent);
        lessonPagesCountValue = new QLabel(parent);

        lessonKeyValueLayout->addRow(lessonPagesCount, lessonPagesCountValue);

        lessonStartButton = new QPushButton(
            QObject::tr("Start training"), parent);

        lessonLayout->addWidget(lessonStartButton);
        lessonLayout->addWidget(lessonNameValue);
        lessonLayout->addLayout(lessonKeyValueLayout);
        lessonLayout->addStretch();
    }
};

#endif // MODULEITEMSINGLEVIEW_H
