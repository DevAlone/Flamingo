#ifndef MODELLISTDISPATCHER_H
#define MODELLISTDISPATCHER_H

#include "modeldispatcher.h"

#include <vector>
#include <memory>

class ModelListDispatcher : public ModelDispatcher
{
public:
    ModelListDispatcher();

    virtual std::vector<std::shared_ptr<Model>> getItemList() = 0;
};

#endif // MODELLISTDISPATCHER_H
