#include "parser/include.h"

#include "htmlanswer.h"
#include "htmlpage.h"
#include "lesson.h"
#include "submodule.h"
#include "textanswer.h"
#include "textpage.h"

#include "mainwindow.h"
#include <QApplication>

// TODO: replace exceptions to logging errors in parsers

#include <iostream>
#include <memory>

using namespace parser;

int main(int argc, char* argv[])
{
    //    ModuleItem* item = new Lesson("");

    //    Lesson* lesson = dynamic_cast<Lesson*>(item);

    //    std::vector<ModuleItem> moduleItems;

    //    moduleItems.push_back(*item);

    //    ModuleItem* item2 = &moduleItems.at(0);
    //    Lesson* lesson2 = dynamic_cast<Lesson*>(item2);

    //    return 0;

    //    QDir dir("courses");
    //    auto entries = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    //    for (auto& entry : entries) {
    //        qDebug() << entry;
    //    }
    //    return 0;

    CoursesParser parser;
    auto logger = std::make_shared<ParserLogger>();
    parser.setLogger(logger);

    std::vector<Course> courses = parser.parseDirectory("courses");

    Course& ielts = courses.at(0);
    Module& listening = ielts.getModules().at(0);
    //    Lesson* lesson2 = dynamic_cast<Lesson*>(&listening.getModuleItems().at(0));

    for (Course& course : courses) {
        std::cout << "Course: " << course.getName().toStdString() << std::endl;
        for (Module& module : course.getModules()) {
            std::cout << " Module: " << module.getName().toStdString() << std::endl;
            for (std::shared_ptr<ModuleItem>& moduleItem : module.getModuleItems()) {
                std::cout << "  Module Item: " << moduleItem->getName().toStdString() << std::endl;
                switch (moduleItem->getType()) {
                case MODULE_ITEM_TYPE::LESSON: {
                    Lesson* lesson = static_cast<Lesson*>(moduleItem.get());

                    std::cout << "   Lesson: " << lesson->getName().toStdString() << std::endl;
                    std::map<unsigned, std::shared_ptr<Page>>& pages = lesson->getPages();

                    for (std::map<unsigned, std::shared_ptr<Page>>::value_type& pageItem : pages) {

                        std::cout << "    Page(" << pageItem.first << "): " << pageItem.second->getNumber() << std::endl;

                        // TODO: show answers
                        auto pageType = pageItem.second->getType();
                        switch (pageType) {
                        case PAGE_TYPE::TEXT: {
                            std::cout << "     Type: text" << std::endl;
                            TextPage* page = static_cast<TextPage*>(pageItem.second.get());
                            std::cout << "     Content: " << page->getContent().toStdString() << std::endl;

                        } break;
                        case PAGE_TYPE::HTML: {
                            std::cout << "     Type: html" << std::endl;
                            HtmlPage* page = static_cast<HtmlPage*>(pageItem.second.get());
                            std::cout << "     Content: " << page->getContent().toStdString() << std::endl;

                        } break;
                        }

                        const auto& answers = pageItem.second->getAnswers();
                        for (const auto& answerItem : answers) {
                            QChar letter = answerItem.first;
                            const auto& answer = answerItem.second;

                            std::cout << "      {" << QString(letter).toStdString() << "} " << std::endl;

                            switch (answer->getType()) {
                            case ANSWER_TYPE::TEXT: {
                                answer.get();
                                TextAnswer* answer = static_cast<TextAnswer*>(answerItem.second.get());
                                std::cout << "       Type: text" << std::endl;
                                std::cout << "       Content: " << answer->getContent().toStdString() << std::endl;

                            } break;
                            case ANSWER_TYPE::HTML: {
                                HtmlAnswer* answer = static_cast<HtmlAnswer*>(answerItem.second.get());
                                std::cout << "       Type: html" << std::endl;
                                std::cout << "       Content: " << answer->getContent().toStdString() << std::endl;
                            } break;
                            }
                        }
                    }
                } break;
                case MODULE_ITEM_TYPE::SUBMODULE:
                    std::cout << "   submodule" << std::endl;
                    break;
                default:
                    break;
                }
            }
        }
    }

    std::cout << std::endl
              << std::endl
              << std::endl;

    auto& logEntries = logger->getEntries();

    for (auto& entry : logEntries) {
        std::clog << entry->toString().toStdString() << std::endl;
    }
    return 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
