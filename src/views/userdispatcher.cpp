#include "userdispatcher.h"

#include <models/user.h>

UserDispatcher::UserDispatcher()
{
}

std::vector<std::shared_ptr<Model>> UserDispatcher::getItems()
{
    std::vector<std::shared_ptr<User>> users = User::getAll();
    std::vector<std::shared_ptr<Model>> models;
    for (auto& user : users) {
        models.push_back(std::static_pointer_cast<Model>(user));
    }

    // TODO: maybe optimize
    return models;
}
