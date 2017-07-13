#ifndef LESSON_H
#define LESSON_H

#include "moduleitem.h"
#include "nullable.hpp"
#include "page.h"

#include <map>
#include <memory>
#include <vector>

class Lesson : public ModuleItem {
public:
    Lesson(const QString& name);

    bool addPage(std::shared_ptr<Page>& page);

    std::map<unsigned, std::shared_ptr<Page>>& getPages();

    Nullable<unsigned char> getLevel() const;
    void setLevel(unsigned char value);

private:
    std::map<unsigned, std::shared_ptr<Page>> pages;
    Nullable<unsigned char> level;
};

#endif // LESSON_H
