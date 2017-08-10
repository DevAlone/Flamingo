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


#ifndef TWOCOLUMNSWIDGET_H
#define TWOCOLUMNSWIDGET_H

#include <QtWidgets>

#include <memory>

class TwoColumnsWidgetUi;

class TwoColumnsWidget : public QWidget {
    Q_OBJECT
public:
    explicit TwoColumnsWidget(QWidget* parent = nullptr);

    void addLeftWidget(QWidget* widget);
    void addRightWidget(QWidget* widget);

    void addLeftLayout(QLayout* layout);
    void addRightLayout(QLayout* layout);

    void setLeftFixedSize(unsigned int px);
signals:

public slots:

private:
    std::unique_ptr<TwoColumnsWidgetUi> ui;
};

class TwoColumnsWidgetUi {
    friend class TwoColumnsWidget;

public:
    TwoColumnsWidgetUi(TwoColumnsWidget* parent)
    {
        mainLayout = new QHBoxLayout;
        leftColumnWidget = new QWidget(parent);
        rightColumnWidget = new QWidget(parent);

        leftColumnLayout = new QVBoxLayout;
        rightColumnLayout = new QVBoxLayout;

        leftColumnWidget->setLayout(leftColumnLayout);
        rightColumnWidget->setLayout(rightColumnLayout);

        mainLayout->addWidget(leftColumnWidget);
        mainLayout->addWidget(rightColumnWidget);
        parent->setLayout(mainLayout);

        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(10);

        leftColumnLayout->setContentsMargins(0, 0, 0, 0);
        leftColumnLayout->setSpacing(5);

        rightColumnLayout->setContentsMargins(0, 0, 0, 0);
        rightColumnLayout->setSpacing(5);
    }

private:
    QHBoxLayout* mainLayout;
    QWidget* leftColumnWidget;
    QWidget* rightColumnWidget;
    QVBoxLayout* leftColumnLayout;
    QVBoxLayout* rightColumnLayout;
};

#endif // TWOCOLUMNSWIDGET_H
