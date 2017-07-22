#include "modellistview.h"

ModelListView::ModelListView(QWidget* parent)
    : ModelView(parent)
{
    ui = std::make_unique<ModelListViewUi>(this);
}

std::shared_ptr<Model> ModelListView::getSelectedModel()
{
    // TODO: just do it
    if (items.empty())
        //        throw std::exception();
        return std::shared_ptr<Model>();
    if (ui->listWidget->currentIndex().row() < 0 || ui->listWidget->currentIndex().row() >= items.size())
        return std::shared_ptr<Model>();

    return items.at(ui->listWidget->currentIndex().row());
}

void ModelListView::updateItems()
{
    // TODO: maybe add exception or qDebug or something else
    if (!dispatcher)
        return;

    items = dispatcher->getItems();
    ui->listWidget->clear();

    for (auto& item : items) {
        ui->listWidget->addItem(static_cast<QString>(*item));
    }
    // TODO: do
    ui->listWidget->setCurrentRow(0);

    // TODO: maybe optimize
}
