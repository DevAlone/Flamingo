#include "modulespagewidget.h"

ModulesPageWidget::ModulesPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<ModulesPageWidgetUi>(this);
}

void ModulesPageWidget::activate(std::shared_ptr<Course> course)
{
    if (course) {
        // update modules
        auto dispatcherWeakPtr = ui->moduleList->getModuleDispatcher();
        if (auto dispatcher = dispatcherWeakPtr.lock()) {
            dispatcher->setCourseIdFilter(course->getId());
            ui->moduleList->updateItems();
        }
    }
}

void ModulesPageWidget::selectedModuleChanged()
{
    ui->moduleView->setModule(ui->moduleList->getSelectedModule());
}
