#ifndef ANSWERTEXTBROWSERWIDGET_H
#define ANSWERTEXTBROWSERWIDGET_H

#include "textbrowserwidget.h"

#include <QWidget>

class AnswerTextBrowserWidget : public TextBrowserWidget {
    Q_OBJECT

public:
    explicit AnswerTextBrowserWidget(QWidget* parent = nullptr);

signals:

public slots:
};

#endif // ANSWERTEXTBROWSERWIDGET_H
