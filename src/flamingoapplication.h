#ifndef FLAMINGOAPPLICATION_H
#define FLAMINGOAPPLICATION_H

#include <QApplication>

class FlamingoApplication : public QApplication {
    Q_OBJECT
public:
    explicit FlamingoApplication(int& argc, char* argv[]);

    // QCoreApplication interface

    virtual bool notify(QObject* obj, QEvent* event);
signals:

public slots:
};

#endif // FLAMINGOAPPLICATION_H
