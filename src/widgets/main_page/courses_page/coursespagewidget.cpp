#include "coursespagewidget.h"
#include "courseparserdialog.h"

#include <parser/include.h>

CoursesPageWidget::CoursesPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<CoursesPageWidgetUi>(this);
}

void CoursesPageWidget::activate()
{
    ui->courseList->updateItems();

    ui->courseView->setCourse(ui->courseList->getSelectedCourse());
}

void CoursesPageWidget::addCourseButtonPressed()
{
    // TODO: add course to current user

    QString selectedCourse = ui->availableCoursesList->getSelectedCourseName();
    if (selectedCourse.isEmpty()) {
        QMessageBox::warning(this,
            QObject::tr("Warning"),
            QObject::tr("Choose course, please"));
        return;
    }
    // TODO: add course

    QSettings s;
    QString courseDirectory = s.value("courseParser/courseDirectory").toString();
    courseDirectory = QDir(courseDirectory).filePath(selectedCourse);

    auto parser = std::make_shared<parser::CoursesParser>();
    auto logger = std::make_shared<parser::ParserLogger>();
    parser->setLogger(logger);

    QStringList directories;
    directories << courseDirectory;

    CourseParserDialog parserDialog(parser, directories);

    if (parserDialog.exec() == QDialog::Accepted) {
        // TODO: add course
        std::vector<std::shared_ptr<Course>> courses = parserDialog.getParsedCourses();

        for (auto& course : courses) {
            course->setUserId(User::getActiveUserId());
            course->save();
        }
        ui->courseList->updateItems();
    }
}

void CoursesPageWidget::selectedCourseChanged()
{
    ui->courseView->setCourse(ui->courseList->getSelectedCourse());
}

void CoursesPageWidget::courseOpenButtonPressed()
{
    std::shared_ptr<Course> course = ui->courseView->getCourse();
    if (!course)
        return;

    if (course->getModules().empty()) {
        QMessageBox::warning(
            this,
            QObject::tr("You can't do that"),
            QObject::tr("This course doesn't contain any modules"));
        return;
    }

    emit goToModulesPage(course);
}
