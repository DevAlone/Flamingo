#ifndef MODULEITEMTREEVIEW_H
#define MODULEITEMTREEVIEW_H

#include "modeltreeview.h"
#include "moduleitemtreedispatcher.h"

#include <memory>

#include <models/moduleitem.h>

class ModuleItemTreeView : public ModelTreeView {
    Q_OBJECT
public:
    explicit ModuleItemTreeView(QWidget* parent = nullptr);

    std::shared_ptr<ModuleItem> getSelectedModuleItem();
    std::shared_ptr<ModuleItemTreeDispatcher> getModuleItemTreeDispatcher() const;
    void setModuleItemTreeDispatcher(std::shared_ptr<ModuleItemTreeDispatcher> dispatcher);
};

#endif // MODULEITEMTREEVIEW_H
