#ifndef LESSON_H
#define LESSON_H

#include "models/moduleitem.h"
#include "page.h"

#include <QSqlError>
#include <map>
#include <memory>
#include <vector>

// TODO: save to database like serialized string
class Lesson : public ModuleItem {
public:
    Lesson(const QString& name);

    bool addPage(std::shared_ptr<Page>& page);

    std::map<unsigned, std::shared_ptr<Page>>& getPages();

    unsigned char getLevel() const;
    void setLevel(unsigned char value);

    virtual void save();

    static QSqlError createTable();

private:
    std::map<unsigned, std::shared_ptr<Page>> pages;
    unsigned char level = 1;
};

#endif // LESSON_H
