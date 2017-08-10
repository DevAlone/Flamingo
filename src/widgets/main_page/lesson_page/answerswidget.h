#ifndef ANSWERSWIDGET_H
#define ANSWERSWIDGET_H

#include "answerslayout.h"

#include <QtWidgets>

#include <memory>

#include <models/lesson/answer.h>

#include <set>

class AnswersWidgetUi;

class AnswersWidget : public QWidget {
    Q_OBJECT
public:
    explicit AnswersWidget(QWidget* parent = nullptr);

    std::set<QChar> getSelectedAnswers();
signals:

public slots:
    void setAnswers(std::map<QChar, std::shared_ptr<Answer>> answers);
    void updateItems();

private:
    std::unique_ptr<AnswersWidgetUi> ui;
    std::map<QChar, std::shared_ptr<Answer>> answers;
    std::vector<AnswerSingleView*> answerViews;
};

class AnswersWidgetUi {
    friend class AnswersWidget;

public:
    AnswersWidgetUi(AnswersWidget* parent)
    {
        mainLayout = new AnswersLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);

        parent->setLayout(mainLayout);
    }

private:
    AnswersLayout* mainLayout;
};

#endif // ANSWERSWIDGET_H
