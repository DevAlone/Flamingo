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

    std::vector<Course>
        courses
        = parser.parseDirectory("courses");

    std::shared_ptr<ModuleItem> moduleItem = courses.at(0).getModules().at(0).getModuleItems().at(0);

    if (moduleItem->getType() == MODULE_ITEM_TYPE::LESSON) {
        auto lesson = std::dynamic_pointer_cast<Lesson>(moduleItem);
        auto submodule = std::dynamic_pointer_cast<Submodule>(moduleItem);

        if (!lesson)
            qDebug() << "ахтунг";

        qDebug() << "3";
        auto& questions = lesson->getQuestions();

        //qDebug() << questions.at(1)->getNumber();
    }

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
