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

protected:
    std::shared_ptr<ModelListDispatcher> dispatcher;

private:
    std::unique_ptr<ModelListViewUi> ui;
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

private:
    QVBoxLayout* layout;
    QListWidget* listWidget;
};

#endif // MODELLISTVIEW_H
