#include "userlistview.h"
#include "userdispatcher.h"

#include <memory>

UserListView::UserListView(QWidget* parent)
    : ModelListView(parent)
{
    dispatcher = std::make_unique<UserDispatcher>();
}

std::shared_ptr<User> UserListView::getSelectedUser()
{
    std::shared_ptr<Model> selectedModel = getSelectedModel();

    std::shared_ptr<User> selectedUser = std::static_pointer_cast<User>(selectedModel);

    return selectedUser;
}
