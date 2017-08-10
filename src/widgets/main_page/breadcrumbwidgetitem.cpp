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


#include "breadcrumbwidgetitem.h"

BreadcrumbWidgetItem::BreadcrumbWidgetItem(const QString& pathItem, QWidget* parent)
    : QPushButton(parent)
    , pathItem(pathItem)
{
}

BreadcrumbWidgetItem::BreadcrumbWidgetItem(const QString& pathItem, const QString& text, QWidget* parent)
    : QPushButton(text, parent)
    , pathItem(pathItem)
{
}

BreadcrumbWidgetItem::BreadcrumbWidgetItem(const QString& pathItem, const QIcon& icon, const QString& text, QWidget* parent)
    : QPushButton(icon, text, parent)
    , pathItem(pathItem)
{
}

QString BreadcrumbWidgetItem::getPathItem() const
{
    return pathItem;
}

bool BreadcrumbWidgetItem::isCurrent() const
{
    return _isCurrent;
}

void BreadcrumbWidgetItem::setCurrentState(bool isCurrent)
{
    _isCurrent = isCurrent;
    style()->unpolish(this);
    style()->polish(this);
    update();
}
