#include "loginpagewidget.h"

LoginPageWidget::LoginPageWidget(QWidget* parent)
    : QWidget(parent)
{
    ui = new LoginPageWidgetUi(this);
}

LoginPageWidget::~LoginPageWidget()
{
    delete ui;
}
