#include "userlistitemwidget.h"

UserListItemWidget::UserListItemWidget(const std::pair<QVariant, QString> &user, QWidget *parent)
    : QLabel(parent)
    , user(user)
{
    setText(user.second);
}

std::pair<QVariant, QString> UserListItemWidget::getUser() const
{
    return user;
}
