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
