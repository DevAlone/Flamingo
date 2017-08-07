#include "modulespagewidget.h"

ModulesPageWidget::ModulesPageWidget(QWidget* parent)
    : AbstractPageWidget(parent)
{
    ui = std::make_unique<ModulesPageWidgetUi>(this);
}

void ModulesPageWidget::activate()
{
    if (course) {
        ui->moduleList->updateItems();
        selectedModuleChanged();
    }
}

void ModulesPageWidget::setCourse(std::shared_ptr<Course> course)
{
    this->course = course;

    // update modules
    auto dispatcherWeakPtr = ui->moduleList->getModuleListDispatcher();
    if (auto dispatcher = dispatcherWeakPtr.lock()) {
        dispatcher->setCourseIdFilter(course->getId());
        ui->moduleList->updateItems();
    }
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
