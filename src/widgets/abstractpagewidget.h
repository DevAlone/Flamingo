#ifndef ABSTRACTPAGEWIDGET_H
#define ABSTRACTPAGEWIDGET_H

#include <QFrame>
#include <QWidget>

class AbstractPageWidget : public QFrame {
    Q_OBJECT
public:
    explicit AbstractPageWidget(QWidget* parent = nullptr);

signals:

public slots:
    virtual void activate();
    virtual void deactivate();
};

#endif // ABSTRACTPAGEWIDGET_H
