#ifndef TWOCOLUMNSWIDGET_H
#define TWOCOLUMNSWIDGET_H

#include <QtWidgets>

#include <memory>

class TwoColumnsWidgetUi;


class TwoColumnsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TwoColumnsWidget(QWidget *parent = nullptr);

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

class TwoColumnsWidgetUi
{
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
    }

private:
    QHBoxLayout* mainLayout;
    QWidget* leftColumnWidget;
    QWidget* rightColumnWidget;
    QVBoxLayout* leftColumnLayout;
    QVBoxLayout* rightColumnLayout;
};

#endif // TWOCOLUMNSWIDGET_H
