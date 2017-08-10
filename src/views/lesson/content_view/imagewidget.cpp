#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget* parent)
    : QLabel(parent)
{
    setMinimumSize(1, 1);
    setScaledContents(false);

    setSizePolicy(
        QSizePolicy::Maximum,
        QSizePolicy::Minimum);
}

QSize ImageWidget::sizeHint() const
{
    QSize size(_pixmap.width(), pixmap()->height());
    return size;
}

QPixmap ImageWidget::scaledPixmap() const
{
    return _pixmap.scaled(
        width(),
        _pixmap.height(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
}

void ImageWidget::setPixmap(const QPixmap& pixmap)
{
    _pixmap = pixmap;
    QLabel::setPixmap(scaledPixmap());
}

void ImageWidget::resizeEvent(QResizeEvent* event)
{
    if (!_pixmap.isNull())
        QLabel::setPixmap(scaledPixmap());
}
