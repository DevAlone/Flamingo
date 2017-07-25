#include "moduleitemspagewidget.h"

ModuleItemsPageWidget::ModuleItemsPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<ModuleItemsPageWidgetUi>(this);
}

void ModuleItemsPageWidget::activate(std::shared_ptr<Module> module)
{
    if (!module)
        return;

    auto dispatcherPtr = ui->moduleItemsTree->getModuleItemTreeDispatcher();
    if (dispatcherPtr) {
        dispatcherPtr->setModuleIdFilter(module->getId());
        ui->moduleItemsTree->updateItems();
    }

    this->module = module;
}

void ModuleItemsPageWidget::selectedModuleItemChanged()
{

    ui->moduleItemView->setModuleItem(ui->moduleItemsTree->getSelectedModuleItem());
}

void ModuleItemsPageWidget::moduleItemOpenButtonPressed()
{
    // TODO: do it
}
