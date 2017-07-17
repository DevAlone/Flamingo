#ifndef USERLISTITEMWIDGET_H
#define USERLISTITEMWIDGET_H

#include <QtWidgets>

class UserListItemWidget : public QLabel {
    Q_OBJECT
public:
    explicit UserListItemWidget(const std::pair<QVariant, QString>& user, QWidget* parent = nullptr);

    std::pair<QVariant, QString> getUser() const;

signals:

public slots:

private:
    std::pair<QVariant, QString> user;
};

#endif // USERLISTITEMWIDGET_H
