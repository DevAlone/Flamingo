#include "coursesparser.h"
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

    auto courses = parser.parseDirectory("courses");

    return 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
