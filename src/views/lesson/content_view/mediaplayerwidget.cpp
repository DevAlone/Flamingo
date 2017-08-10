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



MediaPlayerWidget::MediaPlayerWidget(QWidget* parent)
    : QFrame(parent)
{
    ui = new MediaPlayerWidgetUi(this);

    mediaPlayer = new QMediaPlayer(this);

    mediaPlayer->setVideoOutput(ui->videoWidget);

    connect(
        mediaPlayer, &QMediaPlayer::positionChanged,
        this, &MediaPlayerWidget::mediaPlayerPositionChanged);

    connect(
        mediaPlayer, &QMediaPlayer::durationChanged,
        this, &MediaPlayerWidget::mediaPlayerDurationChanged);

    connect(
        mediaPlayer, &QMediaPlayer::volumeChanged,
        this, &MediaPlayerWidget::mediaPlayerVolumeChanged);

    connect(
        mediaPlayer, &QMediaPlayer::stateChanged,
        this, &MediaPlayerWidget::mediaPlayerStateChanged);

    mediaPlayer->setVolume(50);

    ui->slider->setMinimum(0);
    ui->slider->setMaximum(100);

    ui->volumeSlider->setRange(0, 100);
}

MediaPlayerWidget::~MediaPlayerWidget()
{
    mediaPlayer->stop();
}

void MediaPlayerWidget::setSource(const QString& path)
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(path));
}

void MediaPlayerWidget::playPauseButtonClicked()
{
    if (mediaPlayer->state() == QMediaPlayer::PlayingState)
        mediaPlayer->pause();
    else
        mediaPlayer->play();
}

void MediaPlayerWidget::sliderPositionChanged(int position)
{
    // Осторожно, костыли!
    const QSignalBlocker blocker(mediaPlayer);
    mediaPlayer->setPosition(position);
}

void MediaPlayerWidget::mediaPlayerPositionChanged(qint64 position)
{
    const QSignalBlocker blocker(ui->slider);
    ui->slider->setValue(position);
}

void MediaPlayerWidget::mediaPlayerDurationChanged(qint64 duration)
{
    ui->slider->setRange(0, duration);
}

void MediaPlayerWidget::mediaPlayerStateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState) {
        ui->playPauseButton->setText(tr("pause"));
    } else {
        ui->playPauseButton->setText(tr("play"));
    }
}

void MediaPlayerWidget::mediaPlayerVolumeChanged(int volume)
{
    ui->volumeSlider->setValue(volume);
}

void MediaPlayerWidget::volumeSliderPositionChanged(int position)
{
    mediaPlayer->setVolume(position);
}

void MediaPlayerWidget::fullScreenButtonClicked()
{
    ui->videoWidget->setFullScreen(!ui->videoWidget->isFullScreen());
}
