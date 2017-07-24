#pragma once

#include "modeldispatcher.h"

#include <memory>

class ModelTreeDispatcherItem;

class ModelTreeDispatcher : public ModelDispatcher {
public:
    ModelTreeDispatcher();

    virtual std::vector<ModelTreeDispatcherItem>
    getItemTree() = 0;
};

class ModelTreeDispatcherItem {
public:
    std::shared_ptr<Model> item;
    std::vector<ModelTreeDispatcherItem> children;
};
