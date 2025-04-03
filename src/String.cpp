#include <cstddef>
#include "StringList.h"
#include "String.h"

String::String() = default;

String::String(const char *str)
:string(str) {}

String::String(const string &str)
:string(str) {}

String String::trim(const string &chars) const {
    const String s(c_str());
    std::size_t begin = 0;
    std::size_t end = s.size()-1;

    for(; begin < s.size(); begin++)
        if(chars.find_first_of(s[begin]) == npos)
            break;

    for(; end > begin; end--)
        if(chars.find_first_of(s[end]) == npos)
            break;
    return String(s.substr(begin, end - begin + 1));
}

StringList String::split(const string& delimiter) const {
    String s(c_str());
    std::size_t pos_start = 0, pos_end;
    const std::size_t delim_len = delimiter.length();
    StringList res;
    while ((pos_end = s.find(delimiter, pos_start)) != npos) {
        std::string token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.emplace_back(token);
    }
    res.emplace_back(s.substr(pos_start));
    return res;
}

String String::append(const char * str) const {
    string s(c_str());
    s.append(str);
    return s;
}