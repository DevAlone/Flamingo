#ifndef MODELTREEVIEW_H
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

        mainLayout->addWidget(treeWidget);

        parent->setLayout(mainLayout);

        QObject::connect(
            treeWidget, &QTreeWidget::currentItemChanged,
            parent, &ModelTreeView::selectionChanged);
    }

private:
    QVBoxLayout* mainLayout;
    QTreeWidget* treeWidget;
};

#endif // MODELTREEVIEW_H
