#ifndef MEDIAPLAYERWIDGET_H
#define MEDIAPLAYERWIDGET_H

#include "mediaslider.h"

#include <QtWidgets>

#include <QMediaPlayer>

#include <QtMultimediaWidgets/QVideoWidget>

class MediaPlayerWidgetUi;

class MediaPlayerWidget : public QWidget {
    Q_OBJECT

    friend class MediaPlayerWidgetUi;

public:
    explicit MediaPlayerWidget(QWidget* parent = nullptr);

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

private:
    MediaPlayerWidgetUi* ui;
};

class MediaPlayerWidgetUi : public QObject {
    Q_OBJECT
    friend class MediaPlayerWidget;

public:
    MediaPlayerWidgetUi(MediaPlayerWidget* parent)
        : QObject(parent)
    {
        mainLayout = new QVBoxLayout;
        videoWidget = new QVideoWidget(parent);

        horizontalLayout = new QHBoxLayout;
        playPauseButton = new QPushButton(
            QObject::tr("play"), parent);
        slider = new MediaSlider(parent);
        slider->setOrientation(Qt::Horizontal);
        volumeLabel = new QLabel(
            QObject::tr("Volume"), parent);
        volumeSlider = new MediaSlider(parent);
        volumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(playPauseButton);
        horizontalLayout->addWidget(slider);
        horizontalLayout->addWidget(volumeLabel);
        horizontalLayout->addWidget(volumeSlider);

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
    }

private:
    QVBoxLayout* mainLayout;
    QVideoWidget* videoWidget;

    QHBoxLayout* horizontalLayout;
    QPushButton* playPauseButton;
    MediaSlider* slider;
    QLabel* volumeLabel;
    MediaSlider* volumeSlider;
};

#endif // MEDIAPLAYERWIDGET_H
