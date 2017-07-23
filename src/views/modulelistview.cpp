#include "modulelistview.h"

#include "moduledispatcher.h"

ModuleListView::ModuleListView(QWidget* parent)
    : ModelListView(parent)
{
    dispatcher = std::make_unique<ModuleDispatcher>();
}

std::shared_ptr<Module> ModuleListView::getSelectedModule()
{
    return std::static_pointer_cast<Module>(getSelectedModel());
}

std::weak_ptr<ModuleDispatcher> ModuleListView::getModuleDispatcher() const
{
    return std::dynamic_pointer_cast<ModuleDispatcher>(dispatcher);
}

void ModuleListView::setModuleDispatcher(std::shared_ptr<ModuleDispatcher> dispatcher)
{
    this->dispatcher = dispatcher;
}
