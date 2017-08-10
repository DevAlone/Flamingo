// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



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
    getLastItem()->setCurrentState(false);

    item->setParent(this);

    if (item->getPathItem().contains('/'))
        throw std::logic_error("you cannot set BreadcrumbWidget item with / in path");

    items.push_back(item);
    ui->layout->addWidget(item);

    connect(item, &BreadcrumbWidgetItem::clicked,
        this, &BreadcrumbWidget::itemClicked);

    updateFullPath();
    emit fullPathChanged(fullPath);

    getLastItem()->setCurrentState(true);
}

const QString& BreadcrumbWidget::getFullPath()
{
    return fullPath;
}

BreadcrumbWidgetItem* BreadcrumbWidget::getLastItem() const
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
    getLastItem()->setCurrentState(false);

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

    getLastItem()->setCurrentState(true);
}
