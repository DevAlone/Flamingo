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
