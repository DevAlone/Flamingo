#ifndef MEDIASLIDER_H
#define MEDIASLIDER_H

#include <QtWidgets>

class MediaSlider : public QSlider {
    Q_OBJECT
public:
    explicit MediaSlider(QWidget* parent = nullptr);

signals:

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
};

#endif // MEDIASLIDER_H
