#ifndef BREADCRUMBITEM_H
#define BREADCRUMBITEM_H

#include <QtWidgets>

class BreadcrumbWidgetItem : public QPushButton {
    Q_OBJECT
public:
    explicit BreadcrumbWidgetItem(const QString& pathItem, QWidget* parent = nullptr);
    BreadcrumbWidgetItem(const QString& pathItem, const QString& text, QWidget* parent = nullptr);
    BreadcrumbWidgetItem(const QString& pathItem, const QIcon& icon, const QString& text, QWidget* parent = nullptr);

    QString getPathItem() const;

signals:

public slots:

private:
    QString pathItem;
};

#endif // BREADCRUMBITEM_H
