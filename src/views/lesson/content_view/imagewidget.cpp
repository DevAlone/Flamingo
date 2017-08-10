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
