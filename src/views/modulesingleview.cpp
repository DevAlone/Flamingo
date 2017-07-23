#include "modulesingleview.h"

ModuleSingleView::ModuleSingleView(QWidget* parent)
    : ModelSingleView(parent)
{
    ui = std::make_unique<ModuleSingleViewUi>(this);
}

void ModuleSingleView::setModel(std::shared_ptr<Model> model)
{
    std::shared_ptr<Module> modulePtr = std::dynamic_pointer_cast<Module>(model);

    if (!modulePtr)
        return;

    ModelSingleView::setModel(model);
    module = modulePtr;

    updateData();
}

void ModuleSingleView::setModule(std::shared_ptr<Module> modulePtr)
{
    module = modulePtr;
    model = modulePtr;

    updateData();
}

std::shared_ptr<Module> ModuleSingleView::getModule() const
{
    return module;
}

void ModuleSingleView::updateData()
{
    if (!module)
        return;

    module->update();
    // TODO: update ui
    ui->moduleNameValue->setText(module->getName());
}
