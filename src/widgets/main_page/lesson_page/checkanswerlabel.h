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


#ifndef CHECKANSWERLABEL_H
#define CHECKANSWERLABEL_H

#include <QLabel>

class CheckAnswerLabel : public QLabel {
    Q_OBJECT
    Q_PROPERTY(int completeness READ getCompleteness)
public:
    explicit CheckAnswerLabel(int completeness, const QString& text, QWidget* parent = nullptr);

    int getCompleteness() const;
    void setCompleteness(int value);

signals:

public slots:
    void updateStyle();

private:
    int completeness = 0;
};

#endif // CHECKANSWERLABEL_H
