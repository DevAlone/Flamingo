#include "availablecourseslistwidget.h"

#include <parser/coursesparser.h>

#include <functional>

AvailableCoursesListWidget::AvailableCoursesListWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<AvailableCoursesListWidgetUi>(this);

    updateItems();
}

QString AvailableCoursesListWidget::getSelectedCourseName() const
{
    return ui->courseList->currentText();
}

void AvailableCoursesListWidget::updateItems()
{
    // TODO: переписать этот говнокод
    QString text = ".";
    for (int i = 0; i < 3; i++, text += ".") {
        ui->updateButton->setText(text);
        QTime endTime = QTime::currentTime().addMSecs(100);
        while (QTime::currentTime() < endTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    ui->updateButton->setText("⟳");

    parser::CoursesParser parser;
    // TODO: add logger?

    QSettings s;
    QString dir = s.value("courseParser/courseDirectory").toString();
    items = parser.listCoursesInDirectory(dir);

    ui->courseList->clear();

    for (auto& item : items)
        ui->courseList->addItem(item);

    ui->courseList->setCurrentIndex(0);
}
