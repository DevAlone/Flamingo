#include "moduleitemspagewidget.h"

ModuleItemsPageWidget::ModuleItemsPageWidget(QWidget* parent)
    : AbstractPageWidget(parent)
{
    ui = std::make_unique<ModuleItemsPageWidgetUi>(this);
}

void ModuleItemsPageWidget::activate()
{
    if (this->module) {
        ui->moduleItemsTree->updateItems();
        selectedModuleItemChanged();
    }
}

void ModuleItemsPageWidget::setModule(std::shared_ptr<Module> module)
{
    this->module = module;

    auto dispatcherPtr = ui->moduleItemsTree->getModuleItemTreeDispatcher();
    if (dispatcherPtr) {
        dispatcherPtr->setModuleIdFilter(module->getId());
        ui->moduleItemsTree->updateItems();
    }
}

void ModuleItemsPageWidget::selectedModuleItemChanged()
{

    ui->moduleItemView->setModuleItem(ui->moduleItemsTree->getSelectedModuleItem());
}

void ModuleItemsPageWidget::lessonStartButtonPressed()
{
    std::shared_ptr<ModuleItem> moduleItem
        = ui->moduleItemsTree->getSelectedModuleItem();

    std::shared_ptr<Lesson> lesson
        = std::dynamic_pointer_cast<Lesson>(moduleItem);

    if (!lesson)
        return;

    if (lesson->getPages().empty()) {
        QMessageBox::warning(
            this,
            QObject::tr("You can't do that"),
            QObject::tr("This lesson doesn't contain any pages"));
        return;
    }

    emit goToLessonPage(lesson);
}
