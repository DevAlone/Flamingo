#ifndef MODULELISTVIEW_H
#define MODULELISTVIEW_H

#include "modellistview.h"

#include <QWidget>

#include <models/module.h>

#include "modulelistdispatcher.h"

#include <memory>

class ModuleListView : public ModelListView {
    Q_OBJECT
public:
    explicit ModuleListView(QWidget* parent = nullptr);

    std::shared_ptr<Module> getSelectedModule();
    std::weak_ptr<ModuleListDispatcher> getModuleListDispatcher() const;
    void setModuleDispatcher(std::shared_ptr<ModuleListDispatcher> dispatcher);

signals:

public slots:
};

#endif // MODULELISTVIEW_H
