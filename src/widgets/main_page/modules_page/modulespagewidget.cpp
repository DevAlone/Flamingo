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
