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
    BreadcrumbWidgetItem const* getLastItem() const;

signals:
    void fullPathChanged(const QString& fullPath);

public slots:

private:
    QString fullPath;
    BreadcrumbWidgetUi* ui;
    QVector<BreadcrumbWidgetItem*> items;

private slots:
    void itemClicked();
    void removeLastItem();
    void updateFullPath();
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
