#include "breadcrumbwidget.h"

BreadcrumbWidget::BreadcrumbWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new BreadcrumbWidgetUi(this);

    fullPath = "/";
}

void BreadcrumbWidget::addItem(BreadcrumbWidgetItem* item)
{
    item->setParent(this);

    if (item->getPathItem().contains('/'))
        throw std::logic_error("you cannot set BreadcrumbWidget item with / in path");

    items.push_back(item);
    ui->layout->addWidget(item);

    connect(item, &BreadcrumbWidgetItem::clicked,
        this, &BreadcrumbWidget::itemClicked);
}

const QString& BreadcrumbWidget::getFullPath()
{
    return fullPath;
}

BreadcrumbWidgetItem const* BreadcrumbWidget::getLastItem() const
{
    return items.back();
}

void BreadcrumbWidget::itemClicked()
{
    BreadcrumbWidgetItem* item = qobject_cast<BreadcrumbWidgetItem*>(QObject::sender());

    if (!item) {
        qDebug() << "something weird is happening...";
        return;
    }

    QString prevPath = fullPath;

    for (auto revIt = items.rbegin(); revIt != items.rend(); revIt++) {
        if (*revIt != item) {
            removeLastItem();
        } else
            break;
    }
    updateFullPath();
    if (prevPath != fullPath)
        emit fullPathChanged(fullPath);
}

void BreadcrumbWidget::removeLastItem()
{
    BreadcrumbWidgetItem* item = items.back();
    items.pop_back();
    ui->layout->removeWidget(item);

    // TODO: check it
    delete item;
}

void BreadcrumbWidget::updateFullPath()
{
    fullPath = "/";
    for (BreadcrumbWidgetItem* item : items) {
        fullPath += item->getPathItem() + "/";
    }
}
