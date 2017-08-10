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


#ifndef MODELSINGLEVIEW_H
#define MODELSINGLEVIEW_H

#include "modelview.h"

#include <QWidget>

class ModelSingleView : public ModelView {
    Q_OBJECT
public:
    explicit ModelSingleView(QWidget* parent = nullptr);

    std::shared_ptr<Model> getModel() const;
    void setModel(std::shared_ptr<Model> value);

    static QString returnValueOrPlaceholder(const QString& value, const QString& placeholder = "Unknown");

signals:

public slots:
    virtual void updateData();

protected:
    std::shared_ptr<Model> model;
};

#endif // MODELSINGLEVIEW_H
