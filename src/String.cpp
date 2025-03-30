#include <cstddef>
#include "StringList.h"
#include "String.h"

String::String()
:string() {}

String::String(const char *str)
:string(str) {}

String::String(const string &str)
:string(str) {}

String String::trim(const string &chars) {
    String s(c_str());
    std::size_t begin = 0;
    std::size_t end = s.size()-1;

    for(; begin < s.size(); begin++)
        if(chars.find_first_of(s[begin]) == string::npos)
            break;

    for(; end > begin; end--)
        if(chars.find_first_of(s[end]) == string::npos)
            break;
    return s.substr(begin, end-begin+1);
}

StringList String::split(const string& delimiter) {
    String s(c_str());
    std::size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    StringList res;
    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (s.substr (pos_start));
    return res;
}