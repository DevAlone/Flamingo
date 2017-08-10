#include "courseparserdialog.h"

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
