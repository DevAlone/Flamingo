#include "breadcrumbwidget.h"

BreadcrumbWidget::BreadcrumbWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<BreadcrumbWidgetUi>(this);

    fullPath = "/";

    rootItem = new BreadcrumbWidgetItem("", "", this);
    rootItem->hide();
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

    updateFullPath();
    emit fullPathChanged(fullPath);
}

const QString& BreadcrumbWidget::getFullPath()
{
    return fullPath;
}

const BreadcrumbWidgetItem* BreadcrumbWidget::getLastItem() const
{
    if (items.empty())
        return rootItem;
    return items.back();
}
bool BreadcrumbWidget::cdUp()
{
    if (items.size() > 1) {
        goToItem(items.at(items.size() - 2));
        return true;
    }
    return false;
}

void BreadcrumbWidget::clear()
{
    while (removeLastItem())
        ;
    updateFullPath();
}

void BreadcrumbWidget::itemClicked()
{
    BreadcrumbWidgetItem* item = qobject_cast<BreadcrumbWidgetItem*>(QObject::sender());

    if (!item) {
        qDebug() << "something weird is happening...";
        return;
    }

    goToItem(item);
}

bool BreadcrumbWidget::removeLastItem()
{
    if (items.size() <= 0)
        return false;

    BreadcrumbWidgetItem* item = items.back();
    items.pop_back();
    ui->layout->removeWidget(item);

    // TODO: check it
    item->deleteLater();

    return true;
}

void BreadcrumbWidget::updateFullPath()
{
    fullPath = "/";
    for (BreadcrumbWidgetItem* item : items) {
        fullPath += item->getPathItem() + "/";
    }
}

void BreadcrumbWidget::goToItem(BreadcrumbWidgetItem* item)
{
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
