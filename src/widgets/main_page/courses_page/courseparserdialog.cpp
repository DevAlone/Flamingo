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



CourseParserDialog::CourseParserDialog(std::shared_ptr<parser::CoursesParser>& parser, const QStringList& directories, QWidget* parent)
    : QDialog(parent)
    , directories(directories)
    , parser(parser)
{
    ui = std::make_unique<CourseParserDialogUi>(this);
    okButton = ui->buttons->button(QDialogButtonBox::Ok);
    if (okButton)
        okButton->setEnabled(false);

    thread = std::make_unique<CourseParserDialogThreadHelper>(this);

    thread->start();
    ui->infoLabel->setText(tr("Parsing in progress, wait please"));

    connect(
        thread.get(), &CourseParserDialogThreadHelper::finished,
        this, &CourseParserDialog::threadFinished);

    if (parser->getLogger())
        logger = parser->getLogger();
    else {
        logger = std::make_shared<parser::ParserLogger>();
        parser->setLogger(logger);
    }

    resize(640, 480);
}

CourseParserDialog::~CourseParserDialog()
{
    if (thread)
        thread->wait();
}

std::vector<std::shared_ptr<Course> > CourseParserDialog::getParsedCourses() const
{
    return parsedCourses;
}

void CourseParserDialog::accept()
{
    //    thread->wait();
    if (thread->isRunning())
        return;
    QDialog::accept();
}

void CourseParserDialog::reject()
{
    // TODO: stop thread
    //    thread->wait();

    if (thread->isRunning())
        return;

    QDialog::reject();
}

void CourseParserDialog::threadFinished()
{
    ui->infoLabel->setText(tr("Parsing is finished"));

    ui->logEntriesViewer->updateItems(parser->getLogger());

    // TODO: do something
    if (okButton)
        okButton->setEnabled(true);
}
