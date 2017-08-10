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



TwoColumnsWidget::TwoColumnsWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = std::make_unique<TwoColumnsWidgetUi>(this);
    setLeftFixedSize(300);
}

void TwoColumnsWidget::addLeftWidget(QWidget* widget)
{
    ui->leftColumnLayout->addWidget(widget);
}

void TwoColumnsWidget::addRightWidget(QWidget* widget)
{
    ui->rightColumnLayout->addWidget(widget);
}

void TwoColumnsWidget::addLeftLayout(QLayout* layout)
{
    ui->leftColumnLayout->addLayout(layout);
}

void TwoColumnsWidget::addRightLayout(QLayout* layout)
{
    ui->rightColumnLayout->addLayout(layout);
}

void TwoColumnsWidget::setLeftFixedSize(unsigned int px)
{
    ui->leftColumnWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum));
    ui->leftColumnWidget->setMinimumWidth(px);
    ui->leftColumnWidget->setMaximumHeight(10000000);
}
