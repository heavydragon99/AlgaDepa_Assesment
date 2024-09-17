#ifndef ARTIST_H
#define ARTIST_H

#include "iPerson.h"

class artist : public iPerson {
public:
    artist();
    ~artist();

    void createArt();
};

#endif // ARTIST_H