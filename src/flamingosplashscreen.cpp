#include "flamingosplashscreen.h"

#include <QMouseEvent>

FlamingoSplashScreen::FlamingoSplashScreen(QWidget* parent)
    : QSplashScreen(parent)
{
}

FlamingoSplashScreen::FlamingoSplashScreen(const QPixmap& pixmap)
    : QSplashScreen(pixmap)
{
}

void FlamingoSplashScreen::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton || event->buttons() & Qt::LeftButton)
        return;
    QSplashScreen::mousePressEvent(event);
}

void FlamingoSplashScreen::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton || event->buttons() & Qt::LeftButton)
        return;
    QSplashScreen::mouseReleaseEvent(event);
}

void FlamingoSplashScreen::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton || event->buttons() & Qt::LeftButton)
        return;
    QSplashScreen::mouseDoubleClickEvent(event);
}
