#ifndef TEXTANSWERSINGLEVIEW_H
#define TEXTANSWERSINGLEVIEW_H

#include "answersingleview.h"
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
    std::unique_ptr<TextAnswerSingleViewUi> ui;
    QChar letter;

private:
    std::shared_ptr<TextAnswer> textAnswer;
};

class TextAnswerSingleViewUi {
    friend class TextAnswerSingleView;

public:
    TextAnswerSingleViewUi(TextAnswerSingleView* parent)
    {
        mainLayout = new QVBoxLayout;
        content = new TextBrowserWidget(parent);

        mainLayout->addWidget(content);

        parent->setLayout(mainLayout);
    }

    QVBoxLayout* mainLayout;
    TextBrowserWidget* content;
};

#endif // TEXTANSWERSINGLEVIEW_H
