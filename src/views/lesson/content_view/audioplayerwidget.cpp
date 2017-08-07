#include "audioplayerwidget.h"

AudioPlayerWidget::AudioPlayerWidget(QWidget *parent)
    : MediaPlayerWidget(parent)
{
    ui->videoWidget->hide();
}
