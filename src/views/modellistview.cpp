#include "modellistview.h"

ModelListView::ModelListView(QWidget* parent)
    : ModelView(parent)
{
    ui = std::make_unique<ModelListViewUi>(this);

    auto deleteShortcut = new QShortcut(
        QKeySequence(Qt::Key_Delete),
        this);

    connect(
        deleteShortcut, &QShortcut::activated,
        this, &ModelListView::tryToDeleteSelectedItem);

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(
        ui->listWidget, &QListWidget::customContextMenuRequested,
        this, &ModelListView::showContextMenu);
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

    items = dispatcher->getItemList();
    ui->listWidget->clear();

    for (auto& item : items) {
        ui->listWidget->addItem(static_cast<QString>(*item));
        //        QListWidgetItem* listWidgetItem
        //            = new QListWidgetItem(static_cast<QString>(*item));

        //        ui->listWidget->addItem(listWidgetItem);
        //        ui->listWidget->setItemWidget(listWidgetItem, new QPushButton("delete"));
    }
    // TODO: do
    ui->listWidget->setCurrentRow(0);

    // TODO: maybe optimize
}

void ModelListView::tryToDeleteSelectedItem()
{
}

void ModelListView::showContextMenu(const QPoint& position)
{
}
