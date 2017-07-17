#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new MainWidgetUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::loginAsUser(int userId)
{
    // TODO: check and so on

    // prepare main page
    ui->pages->setCurrentWidget(ui->mainPage);
}
