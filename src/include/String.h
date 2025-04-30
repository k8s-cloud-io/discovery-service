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
        String(const char *);
        String(const std::string &);
        String(const ByteArray &);

		int compare(const String &) const;
        [[nodiscard]] String trim() const;
        [[nodiscard]] StringList split(const std::string&) const;

        String append(const char *) const;

        static String valueOf(int);
};

#endif // STRING_H