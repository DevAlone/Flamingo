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


#ifndef MEDIAPLAYERWIDGET_H
#define MEDIAPLAYERWIDGET_H

#include "mediaplayervideowidget.h"
#include "mediaslider.h"

#include <QtWidgets>

#include <QMediaPlayer>

#include <QtMultimediaWidgets/QVideoWidget>

class MediaPlayerWidgetUi;

// TODO: add checks for file existent
// TODO: add interface to play, stop and pause media
class MediaPlayerWidget : public QFrame {
    Q_OBJECT

    friend class MediaPlayerWidgetUi;

public:
    explicit MediaPlayerWidget(QWidget* parent = nullptr);
    ~MediaPlayerWidget();

signals:

public slots:
    void setSource(const QString& path);

protected:
    QMediaPlayer* mediaPlayer;

private slots:
    void playPauseButtonClicked();
    void sliderPositionChanged(int position);
    void mediaPlayerPositionChanged(qint64 position);
    void mediaPlayerDurationChanged(qint64 duration);
    void mediaPlayerStateChanged(QMediaPlayer::State state);
    void mediaPlayerVolumeChanged(int volume);
    void volumeSliderPositionChanged(int position);

    void fullScreenButtonClicked();

protected:
    MediaPlayerWidgetUi* ui;
};

class MediaPlayerWidgetUi : public QObject {
    Q_OBJECT

public:
    MediaPlayerWidgetUi(MediaPlayerWidget* parent)
        : QObject(parent)
    {
        mainLayout = new QVBoxLayout;
        videoWidget = new MediaPlayerVideoWidget(parent);

        horizontalLayout = new QHBoxLayout;
        playPauseButton = new QPushButton(
            QObject::tr("play"), parent);
        slider = new MediaSlider(parent);
        slider->setOrientation(Qt::Horizontal);
        volumeLabel = new QLabel(
            QObject::tr("Volume"), parent);
        volumeSlider = new MediaSlider(parent);
        volumeSlider->setOrientation(Qt::Horizontal);

        fullScreenButton = new QPushButton(
            QObject::tr("fullscreen"), parent);

        horizontalLayout->addWidget(playPauseButton);
        horizontalLayout->addWidget(slider);
        horizontalLayout->addWidget(volumeLabel);
        horizontalLayout->addWidget(volumeSlider);
        horizontalLayout->addWidget(fullScreenButton);

        mainLayout->addWidget(videoWidget);
        mainLayout->addLayout(horizontalLayout);

        mainLayout->setContentsMargins(0, 0, 0, 0);

        parent->setLayout(mainLayout);

        QObject::connect(
            playPauseButton, &QPushButton::clicked,
            parent, &MediaPlayerWidget::playPauseButtonClicked);

        QObject::connect(
            slider, &QSlider::valueChanged,
            parent, &MediaPlayerWidget::sliderPositionChanged);

        QObject::connect(
            volumeSlider, &QSlider::sliderMoved,
            parent, &MediaPlayerWidget::volumeSliderPositionChanged);

        QObject::connect(
            fullScreenButton, &QPushButton::clicked,
            parent, &MediaPlayerWidget::fullScreenButtonClicked);
    }

    QVBoxLayout* mainLayout;
    MediaPlayerVideoWidget* videoWidget;

    QHBoxLayout* horizontalLayout;
    QPushButton* playPauseButton;
    MediaSlider* slider;
    QLabel* volumeLabel;
    MediaSlider* volumeSlider;

    QPushButton* fullScreenButton;
};

#endif // MEDIAPLAYERWIDGET_H
