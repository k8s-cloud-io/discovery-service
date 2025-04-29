#include <algorithm>
#include <cctype>
#include "HttpResponse.h"
#include "String.h"

using std::transform;

HttpResponse::HttpResponse()
:statusCode(200) {}

unsigned int HttpResponse::getStatusCode() const {
    return statusCode;
}

ByteArray HttpResponse::getBody() const {
    return body;
}

HttpHeaders HttpResponse::getHeaders() const {
    return headers;
}

String HttpResponse::getHeader(const String &value) const {
    String key = value;
    transform(key.begin(), key.end(), key.begin(), [](const unsigned char c){ return std::tolower(c); });
    return !headers.empty() ? headers.at(key) : nullptr;
}

bool HttpResponse::containsHeader(const String &value) const {
    for(const auto &[fst, snd] : headers) {
        String key = value;
        transform(key.begin(), key.end(), key.begin(), [](const unsigned char c){ return std::tolower(c); });
        if(key == fst) return true;
    }
    return false;
}

