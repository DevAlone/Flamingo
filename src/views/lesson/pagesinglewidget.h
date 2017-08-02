#ifndef PAGESINGLEWIDGET_H
#define PAGESINGLEWIDGET_H

#include "answerswidget.h"
#include "pagesingleview.h"

#include <models/lesson/page.h>

#include <QtWidgets>

#include <memory>

class PageSingleWidgetUi;

class PageSingleWidget : public QScrollArea {
    Q_OBJECT

    friend class PageSingleWidgetUi;

public:
    explicit PageSingleWidget(QWidget* parent = nullptr);

signals:
    void goToNextPage();
public slots:
    void setPage(std::shared_ptr<Page> page);
    void updateItems();

private slots:
    void checkAnswerButtonPressed();

private:
    std::unique_ptr<PageSingleWidgetUi> ui;
    std::shared_ptr<Page> page;
};

class PageSingleWidgetUi {
    friend class PageSingleWidget;

public:
    PageSingleWidgetUi(
        PageSingleWidget* parent)
        : PageSingleWidgetUi(
              parent,
              std::shared_ptr<Page>(),
              std::map<QChar, std::shared_ptr<Answer>>())
    {
    }

    PageSingleWidgetUi(
        PageSingleWidget* parent,
        std::shared_ptr<Page> page,
        std::map<QChar, std::shared_ptr<Answer>> answerList)
    {
        baseWidget = new QWidget;
        mainLayout = new QVBoxLayout;

        if (page) {
            pageView = PageSingleView::makePageView(page);

            mainLayout->addWidget(pageView);
        }

        if (!answerList.empty()) {
            answers = new AnswersWidget;

            answers->setAnswers(answerList);

            mainLayout->addWidget(answers);
        }

        mainLayout->addStretch();

        if (!answerList.empty()) {
            nextButton = new QPushButton;
            nextButton->setObjectName("checkAnswerButton");
            nextButton->setText(
                QObject::tr("Check answer"));
            mainLayout->addWidget(nextButton);
            QObject::connect(
                nextButton, &QPushButton::clicked,
                parent, &PageSingleWidget::checkAnswerButtonPressed);
        }

        baseWidget->setLayout(mainLayout);

        parent->setWidget(baseWidget);
        parent->setWidgetResizable(true);
    }

private:
    QWidget* baseWidget;

    QVBoxLayout* mainLayout;

    PageSingleView* pageView;
    AnswersWidget* answers;

    QPushButton* nextButton;
};

#endif // PAGESINGLEWIDGET_H
