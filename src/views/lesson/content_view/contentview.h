#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include <QtWidgets>

#include <memory>

#include <models/lesson/content/content.h>

class ContentViewUi;

class ContentView : public QWidget {
    Q_OBJECT
public:
    explicit ContentView(QWidget* parent = nullptr);

    void clearContents();
    void addContents(const std::vector<std::shared_ptr<Content>>& contents);
    void setContents(const std::vector<std::shared_ptr<Content>>& contents);

    void setText(const QString& text);
    void setHtml(const QString& html);
    void setImage(const QPixmap& pixmap);
    void setImageFile(const QString& _path);
    void setAudioFile(const QString& _path);
    void setVideoFile(const QString& _path);

    void addText(const QString& text);
    void addHtml(const QString& html);
    void addImage(const QPixmap& pixmap);
    void addImageFile(const QString& _path);
    void addAudioFile(const QString& _path);
    void addVideoFile(const QString& _path);

    static ContentView* fromContent(std::shared_ptr<Content> content);

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
