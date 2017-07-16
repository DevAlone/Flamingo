#ifndef FLAMINGOSPLASHSCREEN_H
#define FLAMINGOSPLASHSCREEN_H

#include <QSplashScreen>
#include <QWidget>

class FlamingoSplashScreen : public QSplashScreen {
    Q_OBJECT
public:
    explicit FlamingoSplashScreen(QWidget* parent = nullptr);
    FlamingoSplashScreen(const QPixmap& pixmap);

signals:

public slots:

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
};

#endif // FLAMINGOSPLASHSCREEN_H
