#ifndef MAINPAGEWIDGET_H
#define MAINPAGEWIDGET_H

#include <QtWidgets>

class MainPageWidgetUi;

class MainPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainPageWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    MainPageWidgetUi *ui;
};

class MainPageWidgetUi {
public:
    MainPageWidgetUi(MainPageWidget*parent)
    {
        verticalLayout = new QVBoxLayout(parent);
        testLabel = new QLabel(parent);
        testLabel->setText("Test main page widget");

        verticalLayout->addWidget(testLabel);

        parent->setLayout(verticalLayout);
    }

private:
    QVBoxLayout *verticalLayout;
    QLabel *testLabel;
};

#endif // MAINPAGEWIDGET_H
