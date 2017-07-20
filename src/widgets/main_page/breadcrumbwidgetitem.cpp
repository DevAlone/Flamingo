#include "breadcrumbwidgetitem.h"

BreadcrumbWidgetItem::BreadcrumbWidgetItem(const QString& pathItem, QWidget* parent)
    : QPushButton(parent)
    , pathItem(pathItem)
{
}

BreadcrumbWidgetItem::BreadcrumbWidgetItem(const QString& pathItem, const QString& text, QWidget* parent)
    : QPushButton(text, parent)
    , pathItem(pathItem)
{
}

BreadcrumbWidgetItem::BreadcrumbWidgetItem(const QString& pathItem, const QIcon& icon, const QString& text, QWidget* parent)
    : QPushButton(icon, text, parent)
    , pathItem(pathItem)
{
}

QString BreadcrumbWidgetItem::getPathItem() const
{
    return pathItem;
}
