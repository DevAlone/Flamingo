#ifndef TEXTANSWERSINGLEVIEW_H
#define TEXTANSWERSINGLEVIEW_H

#include "answersingleview.h"
#include "answertextbrowserwidget.h"
#include "textbrowserwidget.h"

#include <QtWidgets>

#include <memory>

#include <models/lesson/textanswer.h>

class TextAnswerSingleViewUi;

class TextAnswerSingleView : public AnswerSingleView {
    Q_OBJECT
public:
    explicit TextAnswerSingleView(QWidget* parent = nullptr);

signals:

public slots:
    void setTextAnswer(QChar letter, std::shared_ptr<TextAnswer> textAnswer);
    void setText(const QString& text);

protected:
    TextAnswerSingleViewUi* answerWidget;

private:
    std::shared_ptr<TextAnswer> textAnswer;
};

class TextAnswerSingleViewUi : public QWidget {
    Q_OBJECT

public:
    TextAnswerSingleViewUi(QWidget* parent)
        : QWidget(parent)
    {
        mainLayout = new QVBoxLayout;
        content = new AnswerTextBrowserWidget(this);

        mainLayout->addWidget(content);

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        setLayout(mainLayout);
    }

    QVBoxLayout* mainLayout;
    AnswerTextBrowserWidget* content;
};

#endif // TEXTANSWERSINGLEVIEW_H
