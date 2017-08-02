#ifndef ANSWERTEXTBROWSERWIDGET_H
#define ANSWERTEXTBROWSERWIDGET_H

#include "textbrowserwidget.h"

#include <QWidget>

class AnswerTextBrowserWidget : public TextBrowserWidget {
    Q_OBJECT
    Q_PROPERTY(bool isChecked READ isChecked WRITE setChecked NOTIFY checkStateChanged)

public:
    explicit AnswerTextBrowserWidget(QWidget* parent = nullptr);

    bool isChecked() const;
    void setChecked(bool isChecked);

signals:
    void checkStateChanged(bool state);

public slots:

protected:
private:
    bool _isChecked = false;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
};

#endif // ANSWERTEXTBROWSERWIDGET_H
