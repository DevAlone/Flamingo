#ifndef ANSWERSLAYOUT_H
#define ANSWERSLAYOUT_H

#include <QtWidgets>

#include <views/lesson/answersingleview.h>

class AnswersLayout : public QVBoxLayout {
    Q_OBJECT
public:
    explicit AnswersLayout(QWidget* parent = nullptr);

    void addAnswer(AnswerSingleView* answerView);
    void clear();

signals:

public slots:

private:
    QHBoxLayout* horizontalLayout = nullptr;
};

#endif // ANSWERSLAYOUT_H
