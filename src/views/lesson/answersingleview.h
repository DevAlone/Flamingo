#ifndef ANSWERSINGLEVIEW_H
#define ANSWERSINGLEVIEW_H

#include <QtWidgets>

#include <views/modelsingleview.h>

#include <models/lesson/answer.h>

#include <memory>

class AnswerSingleViewUi;

class AnswerSingleView : public QFrame {
    Q_OBJECT
    Q_PROPERTY(bool isChecked READ isChecked WRITE setChecked NOTIFY checkStateChanged)

public:
    explicit AnswerSingleView(QWidget* parent = nullptr);

    static AnswerSingleView* makeAnswerView(QChar letter, std::shared_ptr<Answer> answer);

    void setAnswer(QChar letter, std::shared_ptr<Answer> answerPtr);

    std::shared_ptr<Answer> getAnswer() const;

    QChar getLetter() const;
    void setLetter(const QChar& value);

    bool isChecked() const;

signals:
    void checkStateChanged(bool state);
public slots:
    void setChecked(bool isChecked);
    void updateData();

protected:
    QChar letter;
    std::shared_ptr<Answer> answer;
    QWidget* answerWidget = nullptr;
    void setAnswerWidget(QWidget* answerWidget);
    bool _isChecked = false;

private:
    std::unique_ptr<AnswerSingleViewUi> ui;
};

class AnswerSingleViewUi {
    friend class AnswerSingleView;

public:
    AnswerSingleViewUi(AnswerSingleView* parent)
    {
        mainLayout = new QVBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        parent->setLayout(mainLayout);
    }

protected:
    QVBoxLayout* mainLayout;
};

#endif // ANSWERSINGLEVIEW_H
