#ifndef COURSE_H
#define COURSE_H

#include "module.h"

#include <QString>
#include <QVector>

#include <vector>

class Course {
public:
    Course(QString name);

    QString getName() const;
    void setName(const QString& value);
    void addModule(Module& module);
    void addModules(std::vector<Module>& modules);

    QString getAuthor() const;
    void setAuthor(const QString& value);

    unsigned char getLevel() const;
    void setLevel(unsigned char value);

    std::vector<Module>& getModules();

private:
    QString name = "";
    QString author = "";
    unsigned char level = 1;
    std::vector<Module> modules;
};

#endif // COURSE_H