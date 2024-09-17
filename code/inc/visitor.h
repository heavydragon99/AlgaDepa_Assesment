#ifndef VISITOR_H
#define VISITOR_H

#include "iPerson.h"

class visitor : public iPerson {
public:
    visitor();
    ~visitor();

    void someMethod();
};

#endif // VISITOR_H