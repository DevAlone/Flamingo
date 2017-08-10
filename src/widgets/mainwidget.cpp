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


#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<MainWidgetUi>(this);
}

MainWidget::~MainWidget()
{
}

void MainWidget::backToLoginPage()
{
    ui->pages->setCurrentWidget(ui->loginPage);
    ui->loginPage->activate();
}

void MainWidget::loginAsUser(std::shared_ptr<User> user)
{
    // TODO: check and so on

    // prepare main page
    ui->pages->setCurrentWidget(ui->mainPage);
    ui->mainPage->activate();
}
