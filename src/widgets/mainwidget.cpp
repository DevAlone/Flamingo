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
