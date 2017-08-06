#include "mediaslider.h"

MediaSlider::MediaSlider(QWidget* parent)
    : QSlider(parent)
{
}

void MediaSlider::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum() - minimum()) * (height() - event->y())) / height());
        else
            setValue(minimum() + ((maximum() - minimum()) * event->x()) / width());

        event->accept();
    }
    QSlider::mousePressEvent(event);
}

void MediaSlider::mouseMoveEvent(QMouseEvent* event)
{
    QSlider::mouseMoveEvent(event);
}
