#include "modulelistview.h"

#include "modulelistdispatcher.h"

ModuleListView::ModuleListView(QWidget* parent)
    : ModelListView(parent)
{
    dispatcher = std::make_unique<ModuleListDispatcher>();
}

std::shared_ptr<Module> ModuleListView::getSelectedModule()
{
    return std::static_pointer_cast<Module>(getSelectedModel());
}

std::weak_ptr<ModuleListDispatcher> ModuleListView::getModuleListDispatcher() const
{
    return std::dynamic_pointer_cast<ModuleListDispatcher>(dispatcher);
}

void ModuleListView::setModuleDispatcher(std::shared_ptr<ModuleListDispatcher> dispatcher)
{
    this->dispatcher = dispatcher;
}
