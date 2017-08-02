#ifndef ANSWERSWIDGET_H
#define ANSWERSWIDGET_H

#include "answerslayout.h"

#include <QtWidgets>

#include <memory>

#include <models/lesson/answer.h>

class AnswersWidgetUi;

class AnswersWidget : public QWidget {
    Q_OBJECT
public:
    explicit AnswersWidget(QWidget* parent = nullptr);

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

        parent->setLayout(mainLayout);
    }

private:
    AnswersLayout* mainLayout;
};

#endif // ANSWERSWIDGET_H
