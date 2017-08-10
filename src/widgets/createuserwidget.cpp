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



#include <models/user.h>

CreateUserWidget::CreateUserWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<CreateUserWidgetUi>(this);
}

CreateUserWidget::~CreateUserWidget()
{
}

void CreateUserWidget::createButtonClicked()
{
    QString userName = ui->userNameLineEdit->text();

    if (userName.isEmpty()) {
        QMessageBox::warning(this,
            tr("Warning"),
            tr("User name cannot be empty"));
        //        ui->userNameLineEdit->setStyleSheet("QLineEdit { background: rgb(255, 100, 100); }");
        return;
    }
    //    ui->userNameLineEdit->setStyleSheet("");

    //    if (UserManager::getInstance()->addUser(userName))
    //        emit userCreated();

    User user;
    user.setName(userName);
    user.save();

    emit userCreated();
    // TODO: handle error
}
