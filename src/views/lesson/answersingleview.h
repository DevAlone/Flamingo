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


#ifndef ANSWERSINGLEVIEW_H
#define ANSWERSINGLEVIEW_H

#include <QtWidgets>

#include <views/modelsingleview.h>

#include <models/lesson/answer.h>

#include <memory>

class AnswerSingleViewUi;

class AnswerSingleView : public QFrame {
    Q_OBJECT
    Q_PROPERTY(bool isChecked READ isChecked WRITE setChecked NOTIFY checkStateChanged)

public:
    explicit AnswerSingleView(QWidget* parent = nullptr);

    static AnswerSingleView* makeAnswerView(QChar letter, std::shared_ptr<Answer> answer);

    void setAnswer(QChar letter, std::shared_ptr<Answer> answerPtr);

    std::shared_ptr<Answer> getAnswer() const;

    QChar getLetter() const;
    void setLetter(const QChar& value);

    bool isChecked() const;

signals:
    void checkStateChanged(bool state);
public slots:
    void setChecked(bool isChecked);
    void updateData();

protected:
    QChar letter;
    std::shared_ptr<Answer> answer;
    QWidget* answerWidget = nullptr;
    void setAnswerWidget(QWidget* answerWidget);
    bool _isChecked = false;

private:
    std::unique_ptr<AnswerSingleViewUi> ui;
};

class AnswerSingleViewUi {
    friend class AnswerSingleView;

public:
    AnswerSingleViewUi(AnswerSingleView* parent)
    {
        mainLayout = new QVBoxLayout;

        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(5);

        parent->setLayout(mainLayout);
    }

protected:
    QVBoxLayout* mainLayout;
};

#endif // ANSWERSINGLEVIEW_H
