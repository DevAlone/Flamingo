#ifndef BREADCRUMBITEM_H
#define BREADCRUMBITEM_H

#include <QtWidgets>

class BreadcrumbWidgetItem : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(bool isCurrent READ isCurrent WRITE setCurrentState)

public:
    explicit BreadcrumbWidgetItem(const QString& pathItem, QWidget* parent = nullptr);
    BreadcrumbWidgetItem(const QString& pathItem, const QString& text, QWidget* parent = nullptr);
    BreadcrumbWidgetItem(const QString& pathItem, const QIcon& icon, const QString& text, QWidget* parent = nullptr);

    QString getPathItem() const;

    bool isCurrent() const;
    void setCurrentState(bool isCurrent);

signals:

public slots:

private:
    QString pathItem;
    bool _isCurrent = false;
};

#endif // BREADCRUMBITEM_H
