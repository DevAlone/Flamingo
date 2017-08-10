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


#include "pagesingleview.h"

#include "helper.h"

#include "content_view/contentview.h"

#include <models/lesson/audiopage.h>
#include <models/lesson/htmlpage.h>
#include <models/lesson/imagepage.h>
#include <models/lesson/mixedpage.h>
#include <models/lesson/textpage.h>
#include <models/lesson/videopage.h>

PageSingleView::PageSingleView(QWidget* parent)
    : QFrame(parent)
{
    ui = std::make_unique<PageSingleViewUi>(this);
}

PageSingleView* PageSingleView::makePageView(std::shared_ptr<Page> page)
{
    PageSingleView* result = new PageSingleView;

    result->setPage(page);

    return result;
}

void PageSingleView::setPage(std::shared_ptr<Page> pagePtr)
{
    page = pagePtr;

    clearLayout(ui->mainLayout);

    auto contentView = new ContentView;

    switch (page->getType()) {
    case PAGE_TYPE::TEXT: {
        auto textPage = std::static_pointer_cast<TextPage>(page);

        contentView->setText(textPage->getContent());
    } break;
    case PAGE_TYPE::HTML: {
        auto htmlPage = std::static_pointer_cast<HtmlPage>(page);

        contentView->setHtml(htmlPage->getContent());
    } break;
    case PAGE_TYPE::IMAGE: {
        auto imagePage = std::static_pointer_cast<ImagePage>(page);

        contentView->setImageFile(imagePage->getSource());

    } break;
    case PAGE_TYPE::AUDIO: {
        auto audioPage = std::static_pointer_cast<AudioPage>(page);

        contentView->setAudioFile(audioPage->getSource());
    } break;
    case PAGE_TYPE::VIDEO: {
        auto videoPage = std::static_pointer_cast<VideoPage>(page);

        contentView->setVideoFile(videoPage->getSource());
    } break;
    case PAGE_TYPE::MIXED: {
        auto mixedPage = std::static_pointer_cast<MixedPage>(page);

        contentView->setContents(mixedPage->getContents());
    } break;
    default:
        throw Exception(QObject::tr("Unknown page type"));
        break;
    }

    ui->mainLayout->addWidget(contentView);

    ui->mainLayout->setAlignment(contentView, Qt::AlignHCenter);
}

std::shared_ptr<Page> PageSingleView::getPage() const
{
    return page;
}
