#ifndef MEDIAPLAYERVIDEOWIDGET_H
#define MEDIAPLAYERVIDEOWIDGET_H

#include <QVideoWidget>
#include <QtWidgets>

class MediaPlayerVideoWidget : public QVideoWidget {
    Q_OBJECT
public:
    explicit MediaPlayerVideoWidget(QWidget* parent = nullptr);

signals:

public slots:
    void setFullScreen(bool state);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
};

#endif // MEDIAPLAYERVIDEOWIDGET_H
