#ifndef COURSEPARSERWIDGET_H
#define COURSEPARSERWIDGET_H

#include <QtWidgets>

#include "parser/include.h"

#include <memory>

class CourseParserDialogUi;
class CourseParserDialogThreadHelper;

class CourseParserDialog : public QDialog {
    Q_OBJECT
    friend class CourseParserDialogThreadHelper;

public:
    CourseParserDialog(
        std::shared_ptr<parser::CoursesParser>& parser,
        const QStringList& directories,
        QWidget* parent = nullptr);
    virtual ~CourseParserDialog();

    std::vector<std::shared_ptr<Course>> getParsedCourses() const;

signals:

public slots:

private:
    std::unique_ptr<CourseParserDialogUi> ui;
    std::shared_ptr<parser::CoursesParser> parser;
    QStringList directories;
    std::vector<std::shared_ptr<Course>> parsedCourses;
    std::unique_ptr<CourseParserDialogThreadHelper> thread;

    QPushButton* okButton;
    // QDialog interface
public slots:
    virtual void accept();
    virtual void reject();

private slots:
    void threadFinished();
};

class CourseParserDialogUi {
    friend class CourseParserDialog;

public:
    CourseParserDialogUi(CourseParserDialog* parent)
    {
        mainLayout = new QVBoxLayout;
        infoLabel = new QLabel(QObject::tr("Parsing is started"), parent);
        buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        mainLayout->addWidget(infoLabel);
        mainLayout->addWidget(buttons);

        parent->setLayout(mainLayout);

        QObject::connect(buttons, &QDialogButtonBox::accepted,
            parent, &CourseParserDialog::accept);
        QObject::connect(buttons, &QDialogButtonBox::rejected,
            parent, &CourseParserDialog::reject);
    }

private:
    QVBoxLayout* mainLayout;
    QLabel* infoLabel;
    // TODO: log entries viewer
    QDialogButtonBox* buttons;
};

class CourseParserDialogThreadHelper : public QThread {
public:
    CourseParserDialogThreadHelper(CourseParserDialog* parserDialog)
        : QThread()
        , parserDialog(parserDialog)
    {
    }

private:
    CourseParserDialog* parserDialog;

    // QThread interface
protected:
    virtual void run()
    {
        if (!parserDialog->parser)
            return;

        for (auto& courseDir : parserDialog->directories) {
            std::shared_ptr<Course> course = parserDialog->parser->parseCourse(courseDir);
            parserDialog->parsedCourses.push_back(course);
        }
    }
};

#endif // COURSEPARSERWIDGET_H
