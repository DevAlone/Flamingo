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
            parent, &AnswerHeaderWidget::stateChanged);
    }

private:
    QHBoxLayout* mainLayout;
    QCheckBox* checkBox;
};

#endif // ANSWERHEADERWIDGET_H
