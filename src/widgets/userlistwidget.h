#ifndef USERLISTWIDGET_H
#define USERLISTWIDGET_H

#include <QtWidgets>

class UserListWidgetUi;

class UserListWidget : public QWidget {
    Q_OBJECT
public:
    explicit UserListWidget(QWidget* parent = nullptr);
    virtual ~UserListWidget();

signals:

public slots:
    void updateUsers();

private:
    std::vector<std::pair<QVariant, QString>> users;
    UserListWidgetUi* ui = nullptr;
};

class UserListWidgetUi {
    friend class UserListWidget;

public:
    UserListWidgetUi(UserListWidget* parent)
    {
        layout = new QVBoxLayout;

        parent->setLayout(layout);
    }

private:
    QVBoxLayout* layout;
};

#endif // USERLISTWIDGET_H
