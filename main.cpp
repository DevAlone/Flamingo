#include "coursesparser.h"
#include "lesson.h"
#include "submodule.h"

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    //    QDir dir("courses");
    //    auto entries = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    //    for (auto& entry : entries) {
    //        qDebug() << entry;
    //    }
    //    return 0;

    CoursesParser parser;

    std::vector<Course> courses = parser.parseDirectory("courses");

    ModuleItem& moduleItem = courses.at(0).getModules().at(0).getModuleItems().at(0);

    if (moduleItem.getType() == MODULE_ITEM_TYPE::LESSON) {
        Lesson* lesson = dynamic_cast<Lesson*>(&moduleItem);

        // TODO: WTF???
        qDebug() << "3";
        qDebug() << lesson->getQuestions().at(0).val;
    }

    return 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
