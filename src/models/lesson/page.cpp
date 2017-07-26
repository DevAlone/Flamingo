#include "page.h"
#include "htmlpage.h"
#include "textpage.h"

#include <exceptions/pagecreatingerror.h>

std::shared_ptr<Page> Page::createPage(
    unsigned pageNumber,
    std::map<QString, QString>& infoSection,
    std::map<QChar, std::shared_ptr<Answer>>& answers)
{
    static const std::map<QString, PAGE_TYPE> pageTypes = {
        { QString("text"), PAGE_TYPE::TEXT },
        { QString("html"), PAGE_TYPE::HTML },
    };

    PAGE_TYPE type = PAGE_TYPE::TEXT;

    auto typeIt = infoSection.find("type");
    if (typeIt != infoSection.end()) {
        auto enumIt = pageTypes.find(typeIt->second);
        if (enumIt != pageTypes.end())
            type = enumIt->second;
        else
            throw PageCreatingError(
                QObject::tr("Unable to recognize type of page: ")
                + typeIt->second);
    }

    std::shared_ptr<Page> page;

    switch (type) {
    case PAGE_TYPE::TEXT:
        page = std::make_shared<TextPage>(infoSection);
        break;
    case PAGE_TYPE::HTML:
        page = std::make_shared<HtmlPage>(infoSection);
        break;
    }

    page->type = type;
    page->number = pageNumber;

    auto rightAnswersIt = infoSection.find("right answers");
    if (rightAnswersIt != infoSection.end()) {
        page->rightAnswers = RightAnswers::fromString(rightAnswersIt->second);
        const auto& answers = page->rightAnswers.getAnswers();
        if (answers.size() < 1)
            throw PageCreatingError(
                QObject::tr("You have to set at least one right answer: ")
                + rightAnswersIt->second);

        // TODO: check that all right answers exists
    }

    page->answers = answers;

    // TODO: do fucking checks
    //    if (page->answers) {
    //        if (page->answers.size() > 0) {
    //            if (!page->rightAnswers || page->rightAnswers->getAnswers().size() < 1)
    //                throw PageCreatingError(
    //                    QObject::tr("You have to set at least one right answer"));
    //        }
    //    }

    //    if (page->rightAnswers || page->rightAnswers->getAnswers().size() > 0) {
    //        if (page->answers.size() < 1)
    //            throw PageCreatingError(
    //                QObject::tr("You have to set at least one answer"));
    //    }

    return page;
}

unsigned Page::getNumber() const
{
    return number;
}

PAGE_TYPE Page::getType() const
{
    return type;
}

const std::map<QChar, std::shared_ptr<Answer>>& Page::getAnswers() const
{
    return answers;
}

QJsonObject Page::toJsonObject() const
{
    // TODO: do it
    return QJsonObject();
}

std::shared_ptr<Page> Page::fromJsonObject(const QJsonObject& obj)
{
    // TODO: do it
    return std::shared_ptr<Page>();
}
