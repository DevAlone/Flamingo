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


#ifndef ANSWERHEADERWIDGET_H
#define ANSWERHEADERWIDGET_H

#include <QtWidgets>

#include <memory>

class AnswerHeaderWidgetUi;

class AnswerHeaderWidget : public QWidget {
    Q_OBJECT

    friend class AnswerHeaderWidgetUi;

public:
    explicit AnswerHeaderWidget(const QString& text, QWidget* parent = nullptr);

signals:
    void stateChanged(bool state);
public slots:
    void updateStyle();

private slots:
    void checkBoxStateChanged();

private:
    QString text;
    std::unique_ptr<AnswerHeaderWidgetUi> ui;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class AnswerHeaderWidgetUi {
    friend class AnswerHeaderWidget;

public:
    AnswerHeaderWidgetUi(AnswerHeaderWidget* parent)
    {
        mainLayout = new QHBoxLayout;
        checkBox = new QCheckBox(parent->text);

        mainLayout->addWidget(checkBox);

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        parent->setLayout(mainLayout);

        QObject::connect(
            checkBox, &QCheckBox::stateChanged,
            parent, &AnswerHeaderWidget::checkBoxStateChanged);

        //        QObject::connect(
        //            checkBox, &QCheckBox::stateChanged,
        //            parent, &AnswerHeaderWidget::stateChanged);
    }

private:
    QHBoxLayout* mainLayout;
    QCheckBox* checkBox;
};

#endif // ANSWERHEADERWIDGET_H
