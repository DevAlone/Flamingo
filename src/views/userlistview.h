#ifndef USERLISTVIEW_H
#define USERLISTVIEW_H

#include "modellistview.h"

#include <QtWidgets>

#include <models/user.h>

class UserListView : public ModelListView {
    Q_OBJECT
public:
    explicit UserListView(QWidget* parent = nullptr);

    std::shared_ptr<User> getSelectedUser();

signals:

public slots:
    virtual void tryToDeleteSelectedItem();
    virtual void showContextMenu(const QPoint& position);
};

#endif // USERLISTVIEW_H
