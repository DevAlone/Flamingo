#include "parser/include.h"

#include "lesson.h"
#include "submodule.h"

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

    //    auto& logEntries = logger->getEntries();

    //    for (auto& entry : logEntries) {
    //        std::clog << entry->toString().toStdString() << std::endl;
    //    }

    Course& ielts = courses.at(0);
    Module& listening = ielts.getModules().at(0);
    //    Lesson* lesson2 = dynamic_cast<Lesson*>(&listening.getModuleItems().at(0));

    for (Course& course : courses) {
        std::cout << "Course: " << course.getName().toStdString() << std::endl;
        for (Module& module : course.getModules()) {
            std::cout << "\tModule: " << module.getName().toStdString() << std::endl;
            for (std::shared_ptr<ModuleItem>& moduleItem : module.getModuleItems()) {
                std::cout << "\t\tModule Item: " << moduleItem->getName().toStdString() << std::endl;
                switch (moduleItem->getType()) {
                case MODULE_ITEM_TYPE::LESSON: {
                    Lesson* lesson = static_cast<Lesson*>(moduleItem.get());

                    std::cout << "\t\t\tLesson: " << lesson->getName().toStdString() << std::endl;
                    std::map<unsigned, std::shared_ptr<Page>>& pages = lesson->getPages();

                    for (std::map<unsigned, std::shared_ptr<Page>>::value_type& pageItem : pages) {

                        std::cout << "\t\t\t\tPage(" << pageItem.first << "): " << pageItem.second->getNumber() << std::endl;

                        // TODO: show answers
                    }
                } break;
                case MODULE_ITEM_TYPE::SUBMODULE:
                    std::cout << "\t\t\tsubmodule" << std::endl;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
