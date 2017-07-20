#ifndef MODELLISTVIEW_H
#define MODELLISTVIEW_H

#include "modelview.h"

#include <QtWidgets>

#include <vector>

class ModelListViewUi;

class ModelListView : public ModelView {
    Q_OBJECT
public:
    explicit ModelListView(QWidget* parent = nullptr);

    virtual std::shared_ptr<Model> getSelectedModel();

signals:

public slots:
    void updateItems();

private:
    ModelListViewUi* ui;
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
    }

private:
    QVBoxLayout* layout;
    QListWidget* listWidget;
};

#endif // MODELLISTVIEW_H
