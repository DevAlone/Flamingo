#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <QDateTime>
#include <QString>

namespace parser {

enum class LOG_ENTRY_TYPE {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class LogEntry {
public:
    LogEntry(LOG_ENTRY_TYPE type, const QString& message = "");
    virtual ~LogEntry();

    virtual QString toString() const;

    LOG_ENTRY_TYPE getType() const;

    QDateTime getTime() const;

protected:
    LOG_ENTRY_TYPE type;
    QString message;
    QDateTime time;
};
}
#endif // LOGENTRY_H
