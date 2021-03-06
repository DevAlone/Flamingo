// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#ifndef COURSEPARSERWIDGET_H
#define COURSEPARSERWIDGET_H

#include <QtWidgets>

#include "parser/include.h"

#include "logentriesviewerwidget.h"

#include <memory>

#include <parser/logger/parserlogger.h>

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
    std::shared_ptr<parser::ParserLogger> logger;
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

        logEntriesViewer = new LogEntriesViewerWidget(parent);

        mainLayout->addWidget(infoLabel);
        mainLayout->addWidget(logEntriesViewer);
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
    LogEntriesViewerWidget* logEntriesViewer;
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
