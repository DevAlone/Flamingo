#ifndef USERLISTMODEL_H
#define USERLISTMODEL_H

#include "user.h"

#include <QtCore>

class UserListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit UserListModel(QObject* parent = nullptr);

signals:

public slots:
    void updateModel();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
    std::vector<std::shared_ptr<User>> userList;
};

#endif // USERLISTMODEL_H
