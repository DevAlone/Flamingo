#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtWidgets>

class ImageWidget : public QLabel {
    Q_OBJECT
public:
    explicit ImageWidget(QWidget* parent = nullptr);
    virtual QSize sizeHint() const;
    QPixmap scaledPixmap() const;
public slots:
    virtual void setPixmap(const QPixmap& pixmap);
    virtual void resizeEvent(QResizeEvent* event);

signals:

public slots:

private:
    QPixmap _pixmap;
};

#endif // IMAGEWIDGET_H
