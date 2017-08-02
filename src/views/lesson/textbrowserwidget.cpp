#include "textbrowserwidget.h"

#include <climits>

TextBrowserWidget::TextBrowserWidget(QWidget* parent)
    : QTextBrowser(parent)
{
    setSizePolicy(
        QSizePolicy::Minimum,
        QSizePolicy::MinimumExpanding);

    connect(
        this, &TextBrowserWidget::textChanged,
        this, &TextBrowserWidget::updateSize);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QSize TextBrowserWidget::sizeHint()
{
    updateSize();
    return QTextBrowser::sizeHint();
}

void TextBrowserWidget::updateSize()
{
    document()->setTextWidth(viewport()->size().width());
    auto docSize = document()->size().toSize();

    setMinimumWidth(docSize.width());
    setMinimumHeight(docSize.height() + 10);
}
