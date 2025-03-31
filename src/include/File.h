#ifndef FILE_H
#define FILE_H

#include "String.h"

class File {
    public:
        File();
        File(const String &);
        virtual ~File(){}
        String getAbsolutePath() const;
        String getDirectory();

        static bool exists(const String &);
        static bool isDirectory(const String &);

    private:
        String path;
};

#endif