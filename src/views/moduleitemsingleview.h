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
    void lessonStartButtonPressed();
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

        mainLayout->setContentsMargins(0, 0, 0, 0);
        submoduleLayout->setContentsMargins(0, 0, 0, 0);
        lessonLayout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            lessonStartButton, &QPushButton::clicked,
            parent, &ModuleItemSingleView::lessonStartButtonPressed);
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

    QHBoxLayout* lessonTopLayout;
    QLabel* lessonNameValue;
    QLabel* lessonPagesCount;
    QLabel* lessonPagesCountValue;
    QLabel* lessonCompleteness;
    QLabel* lessonCompletenessValue;

    QPushButton* lessonStartButton;

    void makeSubmodulesWidgets(ModuleItemSingleView* parent)
    {
        submoduleNameValue = new QLabel(parent);

        submoduleLayout->addWidget(submoduleNameValue);
        submoduleLayout->addStretch();
    }
    void makeLessonsWidgets(ModuleItemSingleView* parent)
    {
        lessonTopLayout = new QHBoxLayout;

        lessonKeyValueLayout = new QFormLayout;

        lessonNameValue = new QLabel(parent);
        lessonPagesCount = new QLabel(
            QObject::tr("pages"), parent);
        lessonPagesCountValue = new QLabel(parent);
        lessonCompleteness = new QLabel(
            QObject::tr("Completeness"), parent);
        lessonCompletenessValue = new QLabel(parent);

        lessonKeyValueLayout->addRow(
            lessonCompleteness, lessonCompletenessValue);
        lessonKeyValueLayout->addRow(
            lessonPagesCount, lessonPagesCountValue);

        lessonStartButton = new QPushButton(
            QObject::tr("Start training"), parent);

        lessonTopLayout->addWidget(lessonNameValue);
        lessonTopLayout->addWidget(lessonStartButton);

        lessonLayout->addLayout(lessonTopLayout);
        lessonLayout->addLayout(lessonKeyValueLayout);
        lessonLayout->addStretch();
    }
};

#endif // MODULEITEMSINGLEVIEW_H
