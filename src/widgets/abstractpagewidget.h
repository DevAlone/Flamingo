#ifndef ABSTRACTPAGEWIDGET_H
#define ABSTRACTPAGEWIDGET_H

#include <QWidget>

class AbstractPageWidget : public QWidget {
    Q_OBJECT
public:
    explicit AbstractPageWidget(QWidget* parent = nullptr);

signals:

public slots:
    virtual void activate();
    virtual void deactivate();
};

#endif // ABSTRACTPAGEWIDGET_H
