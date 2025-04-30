#ifndef STRING_H
#define STRING_H

#include <string>

#ifndef STRINGLIST_H
#include "StringList.h"
#endif

#ifndef BYTE_ARRAY_H
#include "ByteArray.h"
#endif

class String: public std::string {
    public:
        String();
        virtual ~String() = default;
        String(const char *);
        String(const std::string &);
        String(const ByteArray &);

		int compare(const String &) const;
        [[nodiscard]] String trim();
        [[nodiscard]] StringList split(const std::string&) const;

        String append(const char *);

        static String valueOf(int);
};

#endif // STRING_H