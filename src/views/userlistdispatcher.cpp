#include "userlistdispatcher.h"

#include <models/user.h>

UserListDispatcher::UserListDispatcher()
{
}

std::vector<std::shared_ptr<Model>> UserListDispatcher::getItemList()
{
    std::vector<std::shared_ptr<User>> users = User::getAll();
    std::vector<std::shared_ptr<Model>> models;
    for (auto& user : users) {
        models.push_back(std::static_pointer_cast<Model>(user));
    }

    // TODO: maybe optimize
    return models;
}
