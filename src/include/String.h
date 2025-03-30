#ifndef STRING_H
#define STRING_H

#include "StringList.h"
#include <string>
using std::string;

class String: public string {
    public:
        String();
        String(const char *);
        String(const String &);
        String(const string &);

        static string trim(string, const string &chars = " ");
        static StringList split(const string& s, const string&);
};

#endif // STRING_H