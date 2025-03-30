#ifndef FILE_H
#define FILE_H

#include "String.h"

class File {
    public:
        File(const String &);
        virtual ~File(){}
        String getAbsolutePath() const;
        String getDirectory();

        static bool exists(const String &);
        static bool isDirectory(const String &);

    private:
        File();
        String path;
};

#endif