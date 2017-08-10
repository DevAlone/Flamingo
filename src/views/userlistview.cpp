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
        &UserListView::tryToDeleteSelectedItem);

    userContextMenu.exec(globalPos);
}
