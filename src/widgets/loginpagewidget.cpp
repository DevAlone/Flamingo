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


#include "loginpagewidget.h"

LoginPageWidget::LoginPageWidget(QWidget* parent)
    : AbstractPageWidget(parent)
{
    ui = std::make_unique<LoginPageWidgetUi>(this);
}

LoginPageWidget::~LoginPageWidget()
{
}

//void LoginPageWidget::setActiveUserId(int userId)
//{
//    activeUserId = userId;
//}

//void LoginPageWidget::setActiveUserId(QModelIndex userIndex)
//{
//    ui->userList->setCurrentIndex(userIndex);

//    QVariant obj = ui->userListModel->data(userIndex);
//    if (!obj.isValid())
//        return;

//    User& user = obj.value<User&>();

//    setActiveUserId(user.getId());
//}

void LoginPageWidget::loginButtonClicked()
{
    std::shared_ptr<User> selectedUser;

    try {
        selectedUser = ui->userListView->getSelectedUser();
    } catch (...) {
        // TODO: make normal exception type

        QMessageBox::warning(this,
            tr("Error"),
            tr("Check user please!"));
        return;
    }
    if (!selectedUser) {
        QMessageBox::warning(this,
            tr("Error"),
            tr("1Check user please!"));
        return;
    }

    // TODO: check user and change page

    User::setActiveUserId(selectedUser->getId());

    emit loginAsUser(User::getActiveUser());
}

void LoginPageWidget::activate()
{
    // TODO: do something
    //    ui->userListModel->updateModel();
    ui->userListView->updateItems();
    //    setActiveUserId(ui->userListModel->index(0));
}
