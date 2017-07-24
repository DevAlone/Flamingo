#ifndef MODULEITEMSINGLEVIEW_H
#define MODULEITEMSINGLEVIEW_H

#include <QtWidgets>

#include <views/modelsingleview.h>

#include <memory>

class ModuleItemSingleViewUi;

class ModuleItemSingleView : public ModelSingleView
{
    Q_OBJECT
    friend class ModuleItemSingleViewUi;
public:
    explicit ModuleItemSingleView(QWidget *parent = nullptr);

signals:

public slots:

private:
    std::unique_ptr<ModuleItemSingleViewUi> ui;
};

class ModuleItemSingleViewUi
{
    friend class ModuleItemSingleView;
public:
    ModuleItemSingleViewUi(ModuleItemSingleView* parent)
    {
        mainLayout = new QVBoxLayout;

        parent->setLayout(mainLayout);
    }
private:
    QVBoxLayout *mainLayout;
};

#endif // MODULEITEMSINGLEVIEW_H
