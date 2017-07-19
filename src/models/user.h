#ifndef USERMODEL_H
#define USERMODEL_H

#include "model.h"

#include <QObject>

#include <QSqlError>
#include <memory>
#include <models/course.h>
#include <vector>

class User : public Model {
public:
    User();

    QString getName() const;
    void setName(const QString& name);

    static QSqlError createTable();
    static std::vector<std::shared_ptr<User>> getAll();

    static void setActiveUserId(int userId);
    static int getActiveUserId();

    virtual void save();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    std::vector<Course>& getCourses();

protected:
    QString name = "";
    std::vector<Course> courses;
};
struct UserPrivate {

    static int activeUserId;
};

#endif // USERMODEL_H
