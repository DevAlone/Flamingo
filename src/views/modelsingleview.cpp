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



ModelSingleView::ModelSingleView(QWidget* parent)
    : ModelView(parent)
{
}

std::shared_ptr<Model> ModelSingleView::getModel() const
{
    return model;
}

void ModelSingleView::setModel(std::shared_ptr<Model> value)
{
    model = value;

    updateData();
}

QString ModelSingleView::returnValueOrPlaceholder(const QString& value, const QString& placeholder)
{
    return value.isEmpty() ? placeholder : value;
}

void ModelSingleView::updateData()
{
}
