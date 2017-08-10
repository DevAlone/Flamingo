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


#ifndef MODELLISTVIEW_H
#define MODELLISTVIEW_H

#include "modellistdispatcher.h"
#include "modelview.h"

#include <QtWidgets>

#include <vector>

#include <memory>

class ModelListViewUi;

class ModelListView : public ModelView {
    Q_OBJECT
public:
    explicit ModelListView(QWidget* parent = nullptr);

    virtual std::shared_ptr<Model> getSelectedModel();

signals:
    void selectionChanged();
public slots:
    void updateItems();
    virtual void tryToDeleteSelectedItem();
    virtual void showContextMenu(const QPoint& position);

protected:
    std::shared_ptr<ModelListDispatcher> dispatcher;

    std::unique_ptr<ModelListViewUi> ui;

private:
    std::vector<std::shared_ptr<Model>> items;
};

class ModelListViewUi {
    friend class ModelListView;

public:
    ModelListViewUi(ModelListView* parent)
    {
        layout = new QVBoxLayout;
        listWidget = new QListWidget(parent);
        layout->addWidget(listWidget);

        parent->setLayout(layout);

        layout->setContentsMargins(0, 0, 0, 0);

        QObject::connect(listWidget, &QListWidget::currentTextChanged,
            parent, &ModelListView::selectionChanged);
    }

    QVBoxLayout* layout;
    QListWidget* listWidget;
};

#endif // MODELLISTVIEW_H
