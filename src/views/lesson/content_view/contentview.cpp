#include "contentview.h"

#include "audioplayerwidget.h"
#include "helper.h"
#include "imagewidget.h"
#include "textbrowserwidget.h"
#include "videoplayerwidget.h"

ContentView::ContentView(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<ContentViewUi>(this);

    //    setSizePolicy(
    //        QSizePolicy::Maximum,
    //        QSizePolicy::Minimum);
    setSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Minimum);
}

void ContentView::setText(const QString& text)
{
    clearLayout(ui->mainLayout);
    auto widget = new TextBrowserWidget;

    widget->setPlainText(text);

    ui->mainLayout->addWidget(widget);
}

void ContentView::setHtml(const QString& html)
{
    clearLayout(ui->mainLayout);
    auto widget = new TextBrowserWidget;

    widget->setHtml(html);

    ui->mainLayout->addWidget(widget);
}

void ContentView::setImage(const QPixmap& pixmap)
{
    clearLayout(ui->mainLayout);
    auto widget = new ImageWidget;

    widget->setPixmap(pixmap);

    ui->mainLayout->addWidget(widget);
}

void ContentView::setImageFile(const QString& _path)
{
    // TODO вынести этот функционал в отдельный класс
    QSettings s;
    QDir coursesDir(s.value("courseParser/courseDirectory", "/").toString());
    QString path = coursesDir.absoluteFilePath(_path);

    QPixmap pixmap(path);

    if (pixmap.isNull())
        setHtml(QObject::tr("<h1>Invalid image</h1>"
                            "<h3>File \"")
            + path + QObject::tr("\" doesn't exist</h3>"));
    else
        setImage(pixmap);
}

void ContentView::setAudioFile(const QString& _path)
{
    clearLayout(ui->mainLayout);
    // TODO: вынести в отдельный класс
    QSettings s;
    QDir coursesDir(s.value("courseParser/courseDirectory", "/").toString());
    QString path = coursesDir.absoluteFilePath(_path);

    // TODO: maybe add checks for existent
    auto widget = new AudioPlayerWidget;

    widget->setSource(path);

    ui->mainLayout->addWidget(widget);
}

void ContentView::setVideoFile(const QString& _path)
{
    clearLayout(ui->mainLayout);
    // TODO: вынести в отдельный класс
    QSettings s;
    QDir coursesDir(s.value("courseParser/courseDirectory", "/").toString());
    QString path = coursesDir.absoluteFilePath(_path);

    // TODO: maybe add checks for existent
    auto widget = new VideoPlayerWidget;

    widget->setSource(path);

    ui->mainLayout->addWidget(widget);
}
