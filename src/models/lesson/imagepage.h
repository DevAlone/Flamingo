#ifndef IMAGEPAGE_H
#define IMAGEPAGE_H

#include "mediapage.h"

class ImagePage : public MediaPage {
public:
    ImagePage(std::map<QString, QString>& infoSection);
};

#endif // IMAGEPAGE_H
