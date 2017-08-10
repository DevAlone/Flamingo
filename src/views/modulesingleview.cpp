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



ModuleSingleView::ModuleSingleView(QWidget* parent)
    : ModelSingleView(parent)
{
    ui = std::make_unique<ModuleSingleViewUi>(this);
}

void ModuleSingleView::setModel(std::shared_ptr<Model> model)
{
    std::shared_ptr<Module> modulePtr
        = std::dynamic_pointer_cast<Module>(model);

    if (!modulePtr)
        return;

    ModelSingleView::setModel(model);
    module = modulePtr;

    updateData();
}

void ModuleSingleView::setModule(std::shared_ptr<Module> modulePtr)
{
    module = modulePtr;
    model = modulePtr;

    updateData();
}

std::shared_ptr<Module> ModuleSingleView::getModule() const
{
    return module;
}

void ModuleSingleView::updateData()
{
    if (!module)
        return;

    module->update();

    ui->nameValue->setText(returnValueOrPlaceholder(module->getName()));
    ui->levelValue->setText(QString::number(module->getLevel()));
    ui->descriptionValue->setText(returnValueOrPlaceholder(module->getDescription()));
}
