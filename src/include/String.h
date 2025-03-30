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

        String trim(const string &chars = " ");
        StringList split(const string&);
};

#endif // STRING_H