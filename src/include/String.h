#ifndef STRING_H
#define STRING_H

#include <string>
using std::string;

#ifndef STRINGLIST_H
#include "StringList.h"
#endif

#ifndef BYTE_ARRAY_H
#include "ByteArray.h"
#endif

class String: public string {
    public:
        String();
        String(const char *);
        String(const string &);
        String(const ByteArray &);

		int compare(const String &) const;
        [[nodiscard]] String trim() const;
        [[nodiscard]] StringList split(const string&) const;

        String append(const char *) const;
};

#endif // STRING_H