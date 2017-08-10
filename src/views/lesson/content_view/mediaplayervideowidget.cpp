// Flamingo is an open-source cross platform program for learning languages
// Copyright (C) 2017 Sergey Zakharov
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



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
