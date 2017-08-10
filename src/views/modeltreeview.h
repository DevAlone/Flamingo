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


#define MODELTREEVIEW_H

#include "modeltreedispatcher.h"
#include "modelview.h"

#include <QtWidgets>

#include <memory>

class ModelTreeViewUi;

class ModelTreeView : public ModelView {
    Q_OBJECT
    friend class ModelTreeViewUi;

public:
    explicit ModelTreeView(QWidget* parent = nullptr);

    virtual std::shared_ptr<Model> getSelectedModel();

signals:
    void selectionChanged();
public slots:
    void updateItems();

protected:
    std::shared_ptr<ModelTreeDispatcher> dispatcher;

private:
    std::unique_ptr<ModelTreeViewUi> ui;
};

class ModelTreeViewUi {
    friend class ModelTreeView;

public:
    ModelTreeViewUi(ModelTreeView* parent)
    {
        mainLayout = new QVBoxLayout;
        treeWidget = new QTreeWidget(parent);
        treeWidget->setColumnCount(1);
        treeWidget->setHeaderLabel(
            QObject::tr("Lessons and sub-modules"));

        mainLayout->addWidget(treeWidget);

        parent->setLayout(mainLayout);

        mainLayout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(
            treeWidget, &QTreeWidget::currentItemChanged,
            parent, &ModelTreeView::selectionChanged);
    }

private:
    QVBoxLayout* mainLayout;
    QTreeWidget* treeWidget;
};

#endif // MODELTREEVIEW_H
