#include "coursesparser.h"
#include "courseparserexception.h"
#include "parseerrorexception.h"

#include <QDebug>
#include <iostream>

CoursesParser::CoursesParser(QObject* parent)
    : QObject(parent)
{
}

std::vector<Course> CoursesParser::parseDirectory(const QString& path)
{
    std::vector<Course> courses;

    QDir baseDir(path);

    if (!baseDir.exists())
        throw CourseParserException(tr("Directory ") + path + tr(" doesn't exist"));

    auto entries = baseDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (auto& entry : entries) {
        Course course(entry); // TODO: убедиться, что entry не будет абсолютным путём

        QString courseDirPath = baseDir.absoluteFilePath(entry);

        QFileInfo fileInfo(courseDirPath);

        if (!fileInfo.isDir())
            continue;

        QDir courseDir(courseDirPath);

        QString infoFilePath = courseDir.absoluteFilePath("info.txt");
        QFile infoFile(infoFilePath);

        if (!infoFile.exists())
            throw CourseParserException(
                QString(tr("info.txt file wasn't found here: "))
                + courseDir.absolutePath());

        if (!infoFile.open(QIODevice::ReadOnly))
            throw CourseParserException(
                QString(tr("info.txt can't be opened: "))
                + courseDir.absolutePath() + tr(". Maybe you don't have permissions to do that"));

        {
            QTextStream stream(&infoFile);
            int stringNumber = 0;
            while (!stream.atEnd()) {
                QString line = stream.readLine();

                int indexOfDelemiter = line.indexOf(':');
                if (indexOfDelemiter < 0)
                    continue;
                //                    throw ParseErrorException(
                //                        tr("Error during parsing file ") + infoFilePath
                //                        + tr(": ':' wasn't found in string number ")
                //                        + QString::number(stringNumber) + ": \n" + line);

                QString key = line.left(indexOfDelemiter);
                QString value = line.mid(indexOfDelemiter + 1);
                key = key.simplified().toLower();
                value = value.simplified();

                // TODO: check for empty strings

                std::cout << "key = " << key.toStdString() << "; value = " << value.toStdString() << "; " << std::endl;

                if (key == "author") {
                    course.setAuthor(value);
                } else if (key == "level") {
                    bool isOk;
                    int level = value.toInt(&isOk);
                    if (!isOk || level < 1 || level > 10)
                        throw ParseErrorException(
                            "Unable to recognize level of course. It have to be number in range from 1 to 10",
                            stringNumber);

                    course.setLevel(level);
                }

                stringNumber++;
            }
        }
        infoFile.close();

        courses.push_back(course);
    }

    return courses;
}
