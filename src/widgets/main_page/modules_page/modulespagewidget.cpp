#include "modulespagewidget.h"

ModulesPageWidget::ModulesPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<ModulesPageWidgetUi>(this);
}

void ModulesPageWidget::activate(std::shared_ptr<Course> course)
{
    if (!course) {
        if (this->course) {
            // TODO: change to update method
            ui->moduleList->updateItems();
            selectedModuleChanged();
        }
        return;
    }

    // update modules
    auto dispatcherWeakPtr = ui->moduleList->getModuleListDispatcher();
    if (auto dispatcher = dispatcherWeakPtr.lock()) {
        dispatcher->setCourseIdFilter(course->getId());
        ui->moduleList->updateItems();
    }
    this->course = course;
}

void ModulesPageWidget::selectedModuleChanged()
{
    ui->moduleView->setModule(ui->moduleList->getSelectedModule());
}

void ModulesPageWidget::moduleOpenButtonPressed()
{
    std::shared_ptr<Module> module = ui->moduleView->getModule();

    if (!module)
        return;

    if (module->getModuleItems().empty()) {
        QMessageBox::warning(
            this,
            QObject::tr("You can't do that"),
            QObject::tr("This module doesn't contain any lessons or submodules"));
        return;
    }

    emit goToModuleItemsPage(module);
}
