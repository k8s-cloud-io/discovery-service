#ifndef FILE_H
#define FILE_H

#include "ByteArray.h"
#include "String.h"

class File final {
    public:
        File();
        explicit File(String);
        virtual ~File() = default;

        [[nodiscard]] String getAbsolutePath() const;
        [[nodiscard]] String getFilename() const;
        [[nodiscard]] ByteArray getBytes() const;
        String getDirectory();

        static bool exists(const String &);
        static bool remove(const String &);
        static bool isReadable(const String &);
        static bool isWritable(const String &);
        static bool isDirectory(const String &);

    private:
        String path;
};

#endif