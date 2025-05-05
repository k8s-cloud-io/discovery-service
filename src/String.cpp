#include <algorithm>
#include <cstdarg>
#include <cstddef>
#include <cstring>
#include "String.h"
#include "StringList.h"

String::String() = default;

String::String(const char *str) {
    if (str != nullptr) {
        std::string::append(str);
    }
}

String::String(const ByteArray &str) {
    if(str.size()) {
        const unsigned char *data = str.data();
        std::string::append(reinterpret_cast<const char *>(data));
    }
}

String::String(const std::string &str)
:std::string(str) {}

String String::trim() {
    erase(begin(), std::ranges::find_if(*this, [](const char ch) {
        return !std::isspace(ch);
    }));

    erase(std::find_if(rbegin(), rend(), [](const char ch) {
        return !std::isspace(ch);
    }).base(), end());

    return *this;
}

StringList String::split(const std::string& delimiter) const {
    //String s(c_str());
    ::size_t pos_start = 0, pos_end;
    const std::size_t delim_len = delimiter.length();
    StringList res;

    while ((pos_end = find(delimiter, pos_start)) != npos) {
        std::string token = substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.emplace_back(token);
    }
    res.emplace_back(substr(pos_start));
    return res;
}

String String::append(const char * str) {
    const char *data = str;
    return std::string::append(data);
}

int String::compare(const String &s) const {
    return std::strcmp(c_str(), s.c_str());
}

String String::valueOf(int value) {
    return std::to_string(value);
}

String String::arg(int numArgs, ...) {
    va_list args;
    va_start(args, numArgs);

    for(int i = 0; i < numArgs; i++) {
        String arg = va_arg(args, const char*);
        String argName = String("%") + String::valueOf(i+1);
        size_t pos = std::string::find(argName);
        if(pos != String::npos)
            std::string::replace(pos, argName.length(), arg);
    }
    ::va_end(args);
    return *this;
}