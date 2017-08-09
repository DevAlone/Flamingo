#include "mediaplayervideowidget.h"

MediaPlayerVideoWidget::MediaPlayerVideoWidget(QWidget* parent)
    : QVideoWidget(parent)
{
    //    setLayout(new QVBoxLayout);

    //    layout()->addWidget(new QPushButton("test"));
}

void MediaPlayerVideoWidget::setFullScreen(bool state)
{
    if (state) {
        QSettings s;
        if (!s.value("mediaPlayerWidget/isFullscreenHintShowed", false).toBool()) {
            s.setValue("mediaPlayerWidget/isFullscreenHintShowed", true);
            QMessageBox::warning(this, "Notice", "To exit from fullscreen press Esc");
        }
    }
    QVideoWidget::setFullScreen(state);
}
void MediaPlayerVideoWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen()) {
        setFullScreen(false);
        event->accept();
    } else if (event->key() == Qt::Key_Enter && event->modifiers() & Qt::Key_Alt) {
        setFullScreen(!isFullScreen());
        event->accept();
    }

    QVideoWidget::keyPressEvent(event);
}

void MediaPlayerVideoWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    setFullScreen(!isFullScreen());
    event->accept();
}
