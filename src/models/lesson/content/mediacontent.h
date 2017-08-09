#ifndef MEDIACONTENT_H
#define MEDIACONTENT_H

#include "content.h"

class MediaContent : public Content {
public:
    MediaContent(const QString& source = "");

    QString getSource() const;
    void setSource(const QString& value);

protected:
    QString source = "";
};

#endif // MEDIACONTENT_H
