#ifndef PAGESINGLEWIDGET_H
#define PAGESINGLEWIDGET_H

#include "answerswidget.h"
#include "checkanswerlabel.h"

#include <models/lesson/page.h>

#include <QtWidgets>

#include <memory>

#include <views/lesson/pagesingleview.h>

class PageSingleWidgetUi;

class PageSingleWidget : public QScrollArea {
    Q_OBJECT

    friend class PageSingleWidgetUi;

public:
    explicit PageSingleWidget(QWidget* parent = nullptr);

signals:
    void goToNextPage();
    void checkAnswers(std::set<QChar> answers);
public slots:
    void setPage(std::shared_ptr<Page> page);
    void updateItems();
    void handleUserAnswer(bool isAnswerRight);

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
        checkAnswerLabel = new CheckAnswerLabel(0, "", parent);

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
            checkButton = new QPushButton;
            checkButton->setObjectName("checkAnswerButton");
            checkButton->setText(
                QObject::tr("Check answer"));
            mainLayout->addWidget(checkButton);
            QObject::connect(
                checkButton, &QPushButton::clicked,
                parent, &PageSingleWidget::checkAnswerButtonPressed);
        }

        checkAnswerLabel->hide();
        mainLayout->addWidget(checkAnswerLabel);

        baseWidget->setLayout(mainLayout);

        parent->setWidget(baseWidget);
        parent->setWidgetResizable(true);
    }

private:
    QWidget* baseWidget;

    QVBoxLayout* mainLayout;

    PageSingleView* pageView;
    AnswersWidget* answers;

    QPushButton* checkButton;

    CheckAnswerLabel* checkAnswerLabel;
};

#endif // PAGESINGLEWIDGET_H
