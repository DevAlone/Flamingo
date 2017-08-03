#include "moduleitemsingleview.h"

#include <models/submodule.h>

ModuleItemSingleView::ModuleItemSingleView(QWidget* parent)
    : ModelSingleView(parent)
{
    ui = std::make_unique<ModuleItemSingleViewUi>(this);
}

void ModuleItemSingleView::setModel(std::shared_ptr<Model> model)
{
    std::shared_ptr<ModuleItem> moduleItemPtr
        = std::dynamic_pointer_cast<ModuleItem>(model);

    if (!moduleItemPtr)
        return;

    ModelSingleView::setModel(model);
    moduleItem = moduleItemPtr;

    updateData();
}

void ModuleItemSingleView::setModuleItem(std::shared_ptr<ModuleItem> moduleItemPtr)
{
    ModelSingleView::setModel(moduleItemPtr);
    moduleItem = moduleItemPtr;

    updateData();
}

std::shared_ptr<ModuleItem> ModuleItemSingleView::getModuleItem() const
{
    return moduleItem;
}

void ModuleItemSingleView::updateData()
{
    if (!moduleItem)
        return;

    moduleItem->update();

    std::shared_ptr<Submodule> submodule
        = std::dynamic_pointer_cast<Submodule>(moduleItem);
    std::shared_ptr<Lesson> lesson
        = std::dynamic_pointer_cast<Lesson>(moduleItem);
    if (submodule) {
        ui->showSubmodule();
        ui->submoduleNameValue->setText(
            returnValueOrPlaceholder(submodule->getName()));
    } else if (lesson) {
        ui->showLesson();
        ui->lessonNameValue->setText(
            returnValueOrPlaceholder(lesson->getName()));
        ui->lessonPagesCountValue->setText(
            QString::number(lesson->getPages().size()));
        auto completeness = lesson->getCompleteness();
        double percents = double(completeness.first) / completeness.second * 100;
        ui->lessonCompletenessValue->setText(
            QString::number(percents) + QObject::tr("%"));
    }
}
