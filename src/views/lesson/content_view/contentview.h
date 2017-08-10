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
