#pragma once

#include "modellistdispatcher.h"

class UserListDispatcher : public ModelListDispatcher {
public:
    UserListDispatcher();

    virtual std::vector<std::shared_ptr<Model> > getItemList();
};
