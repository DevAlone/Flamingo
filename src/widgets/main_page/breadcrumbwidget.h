#ifndef BREADCRUMB_H
#define BREADCRUMB_H

#include "breadcrumbwidgetitem.h"

#include <QtWidgets>

class BreadcrumbWidgetUi;

class BreadcrumbWidget : public QWidget {
    Q_OBJECT
public:
    explicit BreadcrumbWidget(QWidget* parent = nullptr);

    void addItem(BreadcrumbWidgetItem* item);

    const QString& getFullPath();
    const BreadcrumbWidgetItem* getLastItem() const;

    bool cdUp();

signals:
    void fullPathChanged(const QString& fullPath);

public slots:
    void clear();

private:
    QString fullPath;
    BreadcrumbWidgetUi* ui;
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

        parent->setLayout(layout);
    }

private:
    QHBoxLayout* layout;
};

#endif // BREADCRUMB_H
