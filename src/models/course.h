#ifndef COURSE_H
#define COURSE_H

#include "module.h"

#include <QSqlError>
#include <QString>
#include <QVector>

#include <vector>

#include <models/model.h>

class Course : public Model {
public:
    Course(QString name);
    virtual operator QString() const;

    QString getName() const;
    void setName(const QString& value);
    void addModule(Module& module);
    void addModules(std::vector<Module>& modules);

    QString getAuthor() const;
    void setAuthor(const QString& value);

    unsigned char getLevel() const;
    void setLevel(unsigned char value);

    std::vector<Module>& getModules();

    int getUserId() const;
    void setUserId(int value);

    virtual void save();
    virtual void sqlInsert();
    virtual void sqlUpdate();

    static QSqlError createTable();
    static std::vector<std::shared_ptr<Course>> getAll();
    static std::vector<std::shared_ptr<Course>> getByUserId(int userId);
    static std::vector<std::shared_ptr<Course>> filter(int userId = -1);

private:
    QString name = "";
    QString author = "";
    unsigned char level = 1;
    std::vector<Module> modules;

    int userId = -1;
};

#endif // COURSE_H
