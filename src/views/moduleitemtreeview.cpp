#include "moduleitemtreeview.h"

ModuleItemTreeView::ModuleItemTreeView(QWidget* parent)
    : ModelTreeView(parent)
{
    dispatcher = std::make_unique<ModuleItemTreeDispatcher>();
}

std::shared_ptr<ModuleItem> ModuleItemTreeView::getSelectedModuleItem()
{
    return std::static_pointer_cast<ModuleItem>(getSelectedModel());
}

std::shared_ptr<ModuleItemTreeDispatcher> ModuleItemTreeView::getModuleItemTreeDispatcher() const
{
    return std::dynamic_pointer_cast<ModuleItemTreeDispatcher>(dispatcher);
}

void ModuleItemTreeView::setModuleItemTreeDispatcher(std::shared_ptr<ModuleItemTreeDispatcher> dispatcher)
{
    this->dispatcher = dispatcher;
}
