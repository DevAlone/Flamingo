#ifndef MODELVIEW_H
#define MODELVIEW_H

#include "modeldispatcher.h"

#include <QWidget>

#include <memory>

class ModelView : public QWidget {
    Q_OBJECT
public:
    explicit ModelView(QWidget* parent = nullptr);

signals:

public slots:

protected:
};

#endif // MODELVIEW_H
