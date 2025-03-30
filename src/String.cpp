#include "String.h"

string String::trim(string s, const string &chars) {
    size_t begin = 0;
    size_t end = s.size()-1;

    for(; begin < s.size(); begin++)
        if(chars.find_first_of(s[begin]) == string::npos)
            break;

    for(; end > begin; end--)
        if(chars.find_first_of(s[end]) == string::npos)
            break;
    return s.substr(begin, end-begin+1);
}

StringList String::split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
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