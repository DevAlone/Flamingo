#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include <QtWidgets>

#include <memory>

class ContentViewUi;

class ContentView : public QWidget {
    Q_OBJECT
public:
    explicit ContentView(QWidget* parent = nullptr);

    void setText(const QString& text);
    void setHtml(const QString& html);
    void setImage(const QPixmap& pixmap);
    void setImageFile(const QString& _path);

signals:

public slots:

private:
    std::unique_ptr<ContentViewUi> ui;
};

class ContentViewUi {
    friend class ContentView;

public:
    ContentViewUi(ContentView* parent)
    {
        mainLayout = new QVBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);

        parent->setLayout(mainLayout);
    }

private:
    QVBoxLayout* mainLayout;
};

#endif // CONTENTVIEW_H
