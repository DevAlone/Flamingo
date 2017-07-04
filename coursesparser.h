#ifndef COURSESPARSER_H
#define COURSESPARSER_H

#include "course.h"

#include <QObject>
#include <QVector>
#include <QtCore>

#include <vector>

class CoursesParser : public QObject {
    Q_OBJECT
public:
    explicit CoursesParser(QObject* parent = nullptr);

    std::vector<Course> parseDirectory(const QString& path);

signals:

public slots:
};

#endif // COURSESPARSER_H
