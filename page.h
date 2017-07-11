#ifndef PAGE_H
#define PAGE_H

#include "answer.h"

#include <memory>
#include <vector>

enum class PAGE_TYPE {
    TEXT,
    HTML
};

class Page {
public:
    Page() = delete;

    // Fabric method which creates page
    // method automatically detect type
    // and creates appropriate class from hierarchy.
    // If one of necessary keys is missing,
    // method can throw exception
    static std::shared_ptr<Page> createPage(
        unsigned pageNumber,
        std::map<QString, QString> infoSection,
        std::map < char, std::shared_ptr<Answer> answersSection)
        = delete;

private:
    unsigned number;
    PAGE_TYPE pageType;
    //std::vector<std::shared_ptr<Answer>> answers;
    //std::map<char, std::shared_ptr<Answer>> answers;
};

#endif // PAGE_H
