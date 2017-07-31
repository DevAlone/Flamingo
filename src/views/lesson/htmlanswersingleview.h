#ifndef HTMLANSWERSINGLEVIEW_H
#define HTMLANSWERSINGLEVIEW_H

#include "textanswersingleview.h"

#include <QtWidgets>

#include <models/lesson/htmlanswer.h>

class HtmlAnswerSingleView : public TextAnswerSingleView {
    Q_OBJECT
public:
    explicit HtmlAnswerSingleView(QWidget* parent = nullptr);

    void setTextAnswer(QChar letter, std::shared_ptr<TextAnswer> textAnswer) = delete;
    void setHtmlAnswer(QChar letter, std::shared_ptr<HtmlAnswer> htmlAnswer);

    void setHtml(const QString& html);
signals:

public slots:

private:
    std::shared_ptr<HtmlAnswer> htmlAnswer;
};

#endif // HTMLANSWERSINGLEVIEW_H
