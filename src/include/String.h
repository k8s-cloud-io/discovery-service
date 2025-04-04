#ifndef STRING_H
#define STRING_H

#include <string>
using std::string;

#ifndef STRINGLIST_H
#include "StringList.h"
#endif

class String: public string {
    public:
        String();
        String(const char *);
        String(const string &);

        [[nodiscard]] String trim(const string &chars = " ") const;
        [[nodiscard]] StringList split(const string&) const;

        String append(const char *) const;
};

#endif // STRING_H