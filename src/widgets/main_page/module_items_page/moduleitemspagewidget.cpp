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
