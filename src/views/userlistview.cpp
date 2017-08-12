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

#include "userlistview.h"
#include "userlistdispatcher.h"

#include <memory>

UserListView::UserListView(QWidget* parent)
    : ModelListView(parent)
{
    dispatcher = std::make_unique<UserListDispatcher>();
}

std::shared_ptr<User> UserListView::getSelectedUser()
{
    std::shared_ptr<Model> selectedModel = getSelectedModel();

    std::shared_ptr<User> selectedUser = std::static_pointer_cast<User>(selectedModel);

    return selectedUser;
}

void UserListView::tryToDeleteSelectedItem()
{
    auto selectedUser = getSelectedUser();

    if (!selectedUser)
        return;

    if (QMessageBox::question(this,
            QObject::tr("Delete user?"),
            QObject::tr("Are you sure you want to delete this user?")
                + "\n " + selectedUser->getName(),
            QMessageBox::Yes | QMessageBox::No)
        == QMessageBox::Yes) {
        selectedUser->remove();
        updateItems();
    }
}

void UserListView::showContextMenu(const QPoint& position)
{
    QPoint globalPos = ui->listWidget->mapToGlobal(position);

    QMenu userContextMenu;
    userContextMenu.addAction(
        QObject::tr("Delete selected user"),
        this,
        SLOT(tryToDeleteSelectedItem()));
    //&UserListView::tryToDeleteSelectedItem);

    userContextMenu.exec(globalPos);
}
