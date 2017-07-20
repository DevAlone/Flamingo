#ifndef USERDISPATCHER_H
#define USERDISPATCHER_H

#include "modeldispatcher.h"



class UserDispatcher : public ModelDispatcher
{
public:
    UserDispatcher();

    virtual std::vector<std::shared_ptr<Model> > getItems();
};



#endif // USERDISPATCHER_H
