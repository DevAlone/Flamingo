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



AnswerHeaderWidget::AnswerHeaderWidget(const QString& text, QWidget* parent)
    : QWidget(parent)
    , text(text)
{
    ui = std::make_unique<AnswerHeaderWidgetUi>(this);
}

void AnswerHeaderWidget::updateStyle()
{
    style()->unpolish(this);
    style()->polish(this);
    update();
    ui->checkBox->style()->unpolish(ui->checkBox);
    ui->checkBox->style()->polish(ui->checkBox);
    ui->checkBox->update();
}

void AnswerHeaderWidget::checkBoxStateChanged()
{
    updateStyle();
    emit stateChanged(ui->checkBox->isChecked());
}

void AnswerHeaderWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton || event->buttons() | Qt::LeftButton) {
        ui->checkBox->setChecked(!ui->checkBox->isChecked());
    }
}
