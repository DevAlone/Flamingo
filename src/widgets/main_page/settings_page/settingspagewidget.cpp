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


#include "settingspagewidget.h"

SettingsPageWidget::SettingsPageWidget(QWidget* parent)
    : AbstractPageWidget(parent)
{
    ui = std::make_unique<SettingsPageWidgetUi>(this);
}

void SettingsPageWidget::activate()
{
    QSettings s;

    ui->courseDirectoryValue->setText(
        s.value("courseParser/courseDirectory", "courses").toString());
    auto autoSwitchTime = s.value("interface/lesson/pageAutoSwitchTime", 500).toInt();
    ui->pageAutoSwitchTrigger->setChecked(autoSwitchTime >= 0);
    if (autoSwitchTime >= 0)
        ui->pageAutoSwitchTimeValue->setValue(autoSwitchTime);
}

void SettingsPageWidget::saveButtonClicked()
{
    QSettings s;
    s.setValue("courseParser/courseDirectory", ui->courseDirectoryValue->text());

    if (ui->pageAutoSwitchTrigger->isChecked())
        s.setValue("interface/lesson/pageAutoSwitchTime", ui->pageAutoSwitchTimeValue->value());
    else
        s.setValue("interface/lesson/pageAutoSwitchTime", -1);

    emit goToBackPage();
}
