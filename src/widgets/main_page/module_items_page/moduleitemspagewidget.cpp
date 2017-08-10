// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



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
