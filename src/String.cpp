#include <algorithm>
#include <cstddef>
#include <cstring>
#include "String.h"
#include "StringList.h"

inline String ltrim(String &s) {
    s.erase(s.begin(), std::ranges::find_if(s, [](const unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

// trim from end (in place)
inline String rtrim(String &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](const unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

String::String() = default;

String::String(const char *str)
:string() {
    if (str != nullptr && strlen(str) > 0) {
        string::append(str);
    }
}

String::String(const ByteArray &str)
:string(str.data()) {}

String::String(const string &str)
:string(str) {}

String String::trim() const {
    String s = c_str();
    s = ltrim(s);
    s = rtrim(s);
    return s;
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
    if (str == nullptr) {
        return s;
    }

    s.append(str);
    return s;
}

int String::compare(const String &s) const {
    return std::strcmp(c_str(), s.c_str());
}