#ifndef TEXTPAGESINGLEVIEW_H
#define TEXTPAGESINGLEVIEW_H

#include "pagesingleview.h"

#include <QtWidgets>

#include <memory>

#include <models/lesson/textpage.h>

class TextPageSingleViewUi;

class TextPageSingleView : public PageSingleView {
    Q_OBJECT
public:
    explicit TextPageSingleView(QWidget* parent = nullptr);

signals:

public slots:
    void setTextPage(std::shared_ptr<TextPage> textPage);
    void setContent(const QString& data);

protected:
    std::unique_ptr<TextPageSingleViewUi> ui;

private:
    std::shared_ptr<TextPage> textPage;
};
class TextPageSingleViewUi {

public:
    TextPageSingleViewUi(TextPageSingleView* parent)
    {
        mainLayout = new QVBoxLayout;
        content = new QLabel(parent);

        mainLayout->addWidget(content);

        parent->setLayout(mainLayout);
    }

    QVBoxLayout* mainLayout;
    QLabel* content;
};

#endif // TEXTPAGESINGLEVIEW_H
