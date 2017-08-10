#include "modeltreeview.h"

Q_DECLARE_METATYPE(std::shared_ptr<Model>)

ModelTreeView::ModelTreeView(QWidget* parent)
    : ModelView(parent)
{
    ui = std::make_unique<ModelTreeViewUi>(this);
}

std::shared_ptr<Model> ModelTreeView::getSelectedModel()
{
    std::shared_ptr<Model> result;

    QTreeWidgetItem* currentItem = ui->treeWidget->currentItem();
    if (currentItem) {
        QVariant v = currentItem->data(0, Qt::UserRole);
        if (v.isValid()) {
            result = v.value<std::shared_ptr<Model>>();
        }
    }

    return result;
}

void processModelChildren(QTreeWidgetItem* parent, ModelTreeDispatcherItem* item)
{
    if (!item->item)
        return;

    auto treeWidgetItem = new QTreeWidgetItem(parent);
    treeWidgetItem->setData(0, Qt::UserRole, QVariant::fromValue(item->item));
    treeWidgetItem->setText(0, *item->item);

    for (auto& child : item->children)
        processModelChildren(treeWidgetItem, &child);
}

void ModelTreeView::updateItems()
{
    if (!dispatcher)
        return;

    std::vector<ModelTreeDispatcherItem> items = dispatcher->getItemTree();

    ui->treeWidget->clear();

    for (auto& item : items) {
        std::shared_ptr<Model> rootModel = item.item;
        auto treeWidgetRootItem = new QTreeWidgetItem(ui->treeWidget);
        treeWidgetRootItem->setData(0, Qt::UserRole, QVariant::fromValue(rootModel));
        treeWidgetRootItem->setText(0, *rootModel);

        for (auto& child : item.children)
            processModelChildren(treeWidgetRootItem, &child);
    }

    if (ui->treeWidget->topLevelItemCount() > 0) {
        ui->treeWidget->setCurrentItem(ui->treeWidget->topLevelItem(0));
    }
}
