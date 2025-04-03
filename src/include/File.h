#ifndef FILE_H
#define FILE_H

#include "String.h"

class File {
    public:
        File();
        explicit File(String );

        virtual ~File()= default;
        [[nodiscard]] String getAbsolutePath() const;
        String getDirectory();

        static bool exists(const String &);
        static bool isDirectory(const String &);

    private:
        String path;
};

#endif