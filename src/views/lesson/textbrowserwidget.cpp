#include "textbrowserwidget.h"

#include <climits>

TextBrowserWidget::TextBrowserWidget(QWidget* parent)
    : QTextBrowser(parent)
{
    setSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Minimum);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QSize TextBrowserWidget::sizeHint() const
{
    if (document()) {
        auto docSize = document()->size();
        return QSize(docSize.width(), docSize.height() + 10);
    } else
        return QTextBrowser::sizeHint();
}
