#ifndef DIR_H
#define DIR_H

#include "String.h"

class Dir {
    public:
        virtual ~Dir() = default;
        static String currentDir();
};

#endif // DIR_H