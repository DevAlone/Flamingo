#include "contentview.h"

#include "audioplayerwidget.h"
#include "helper.h"
#include "imagewidget.h"
#include "textbrowserwidget.h"
#include "videoplayerwidget.h"

#include <exceptions/exception.h>

#include <models/lesson/content/audiocontent.h>
#include <models/lesson/content/htmlcontent.h>
#include <models/lesson/content/imagecontent.h>
#include <models/lesson/content/textcontent.h>
#include <models/lesson/content/videocontent.h>

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

void ContentView::addContents(const std::vector<std::shared_ptr<Content> >& contents)
{
    for (auto& content : contents) {
        switch (content->getType()) {
        case CONTENT_TYPE::TEXT: {
            auto textContent = std::static_pointer_cast<TextContent>(content);
            addText(textContent->getText());
        } break;
        case CONTENT_TYPE::HTML: {
            auto htmlContent = std::static_pointer_cast<HtmlContent>(content);
            addHtml(htmlContent->getHtml());
        } break;
        case CONTENT_TYPE::IMAGE: {
            auto imageContent = std::static_pointer_cast<ImageContent>(content);
            addImageFile(imageContent->getSource());
        } break;
        case CONTENT_TYPE::AUDIO: {
            auto audioContent = std::static_pointer_cast<AudioContent>(content);
            addAudioFile(audioContent->getSource());
        } break;
        case CONTENT_TYPE::VIDEO: {
            auto videoContent = std::static_pointer_cast<VideoContent>(content);
            addVideoFile(videoContent->getSource());
        } break;
        default:
            throw Exception(tr("Unrecognized Content type"));
            break;
        }
    }
}

void ContentView::setContents(const std::vector<std::shared_ptr<Content> >& contents)
{
    clearContents();
    addContents(contents);
}

void ContentView::clearContents()
{
    clearLayout(ui->mainLayout);
}

void ContentView::setText(const QString& text)
{
    clearContents();
    addText(text);
}

void ContentView::setHtml(const QString& html)
{
    clearContents();
    addHtml(html);
}

void ContentView::setImage(const QPixmap& pixmap)
{
    clearContents();
    addImage(pixmap);
}

void ContentView::setImageFile(const QString& _path)
{
    clearContents();
    addImageFile(_path);
}

void ContentView::setAudioFile(const QString& _path)
{
    clearContents();
    addAudioFile(_path);
}

void ContentView::setVideoFile(const QString& _path)
{
    clearContents();
    addVideoFile(_path);
}

void ContentView::addText(const QString& text)
{
    auto widget = new QLabel; //new TextBrowserWidget;

    //    widget->setPlainText(text);
    widget->setText(text);

    ui->mainLayout->addWidget(widget);
}

void ContentView::addHtml(const QString& html)
{
    auto widget = new TextBrowserWidget;

    widget->setHtml(html);

    ui->mainLayout->addWidget(widget);
}

void ContentView::addImage(const QPixmap& pixmap)
{
    auto widget = new ImageWidget;

    widget->setPixmap(pixmap);

    ui->mainLayout->addWidget(widget);
}

void ContentView::addImageFile(const QString& _path)
{ // TODO вынести этот функционал в отдельный класс
    QSettings s;
    QDir coursesDir(s.value("courseParser/courseDirectory", "/").toString());
    QString path = coursesDir.absoluteFilePath(_path);

    QPixmap pixmap(path);

    if (pixmap.isNull())
        addHtml(QObject::tr("<h1>Invalid image</h1>"
                            "<h3>File \"")
            + path + QObject::tr("\" doesn't exist</h3>"));
    else
        addImage(pixmap);
}

void ContentView::addAudioFile(const QString& _path)
{
    // TODO: вынести в отдельный класс
    QSettings s;
    QDir coursesDir(s.value("courseParser/courseDirectory", "/").toString());
    QString path = coursesDir.absoluteFilePath(_path);

    // TODO: maybe add checks for existent
    auto widget = new AudioPlayerWidget;

    widget->setSource(path);

    ui->mainLayout->addWidget(widget);
}

void ContentView::addVideoFile(const QString& _path)
{
    // TODO: вынести в отдельный класс
    QSettings s;
    QDir coursesDir(s.value("courseParser/courseDirectory", "/").toString());
    QString path = coursesDir.absoluteFilePath(_path);

    // TODO: maybe add checks for existent
    auto widget = new VideoPlayerWidget;

    widget->setSource(path);

    ui->mainLayout->addWidget(widget);
}

ContentView* ContentView::fromContent(std::shared_ptr<Content> content)
{
    ContentView* result = new ContentView;
    switch (content->getType()) {
    case CONTENT_TYPE::TEXT: {
        auto textContent = std::static_pointer_cast<TextContent>(content);
        result->setText(textContent->getText());
    } break;
    case CONTENT_TYPE::HTML: {
        auto htmlContent = std::static_pointer_cast<HtmlContent>(content);
        result->setHtml(htmlContent->getHtml());
    } break;
    case CONTENT_TYPE::IMAGE: {
        auto imageContent = std::static_pointer_cast<ImageContent>(content);
        result->setImageFile(imageContent->getSource());
    } break;
    case CONTENT_TYPE::AUDIO: {
        auto audioContent = std::static_pointer_cast<AudioContent>(content);
        result->setAudioFile(audioContent->getSource());
    } break;
    case CONTENT_TYPE::VIDEO: {
        auto videoContent = std::static_pointer_cast<VideoContent>(content);
        result->setVideoFile(videoContent->getSource());
    } break;
    default:
        throw Exception(tr("Unrecognized Content type"));
        break;
    }
    return result;
}
