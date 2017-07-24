#ifndef AVAILABLECOURSESLISTWIDGET_H
#define AVAILABLECOURSESLISTWIDGET_H

#include <QtWidgets>

#include <memory>

class AvailableCoursesListWidgetUi;

class AvailableCoursesListWidget : public QWidget {
    Q_OBJECT
public:
    explicit AvailableCoursesListWidget(QWidget* parent = nullptr);

    QString getSelectedCourseName() const;
signals:

public slots:
    void updateItems();

private:
    std::vector<QString> items;
    std::unique_ptr<AvailableCoursesListWidgetUi> ui;
};

class AvailableCoursesListWidgetUi {
    friend class AvailableCoursesListWidget;

public:
    AvailableCoursesListWidgetUi(AvailableCoursesListWidget* parent)
    {
        layout = new QHBoxLayout;
        updateButton = new QPushButton(QObject::tr("⟳", "update courses button"), parent);
        updateButton->setToolTip("update course list");

        courseList = new QComboBox(parent);
        layout->addWidget(updateButton, 1);
        layout->addWidget(courseList, 5);

        parent->setLayout(layout);

        QObject::connect(
            updateButton, &QPushButton::clicked,
            parent, &AvailableCoursesListWidget::updateItems);
    }

private:
    QHBoxLayout* layout;
    QPushButton* updateButton;
    QComboBox* courseList;
};

#endif // AVAILABLECOURSESLISTWIDGET_H
