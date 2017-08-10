#ifndef TEXTBROWSERWIDGET_H
#define TEXTBROWSERWIDGET_H

#include <QtWidgets>

class TextBrowserWidget : public QTextBrowser {
    Q_OBJECT
public:
    explicit TextBrowserWidget(QWidget* parent = nullptr);

    virtual QSize sizeHint();
signals:

public slots:

private:
    void updateSize();
};

#endif // TEXTBROWSERWIDGET_H
