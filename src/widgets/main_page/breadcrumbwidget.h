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


#define BREADCRUMB_H

#include "breadcrumbwidgetitem.h"

#include <QtWidgets>

#include <memory>

class BreadcrumbWidgetUi;

class BreadcrumbWidget : public QWidget {
    Q_OBJECT
public:
    explicit BreadcrumbWidget(QWidget* parent = nullptr);

    void addItem(BreadcrumbWidgetItem* item);

    const QString& getFullPath();
    BreadcrumbWidgetItem* getLastItem() const;

    bool cdUp();

signals:
    void fullPathChanged(const QString& fullPath);

public slots:
    void clear();

private:
    std::unique_ptr<BreadcrumbWidgetUi> ui;
    QString fullPath;
    BreadcrumbWidgetItem* rootItem;
    QVector<BreadcrumbWidgetItem*> items;

private slots:
    void itemClicked();
    bool removeLastItem();
    void updateFullPath();
    void goToItem(BreadcrumbWidgetItem* item);
};

class BreadcrumbWidgetUi {
    friend class BreadcrumbWidget;

public:
    BreadcrumbWidgetUi(BreadcrumbWidget* parent)
    {
        layout = new QHBoxLayout(parent);

        layout->setContentsMargins(0, 0, 0, 0);

        parent->setLayout(layout);
    }

private:
    QHBoxLayout* layout;
};

#endif // BREADCRUMB_H
