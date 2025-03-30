#include <algorithm>
#include <cctype>
#include "String.h"
#include "HttpResponse.h"

using std::transform;

HttpResponse::HttpResponse()
:statusCode(200) {}

unsigned int HttpResponse::getStatusCode() const {
    return statusCode;
}

CharBuffer HttpResponse::getBody() const {
    return body;
}

HttpHeaders HttpResponse::getHeaders() {
    return headers;
}

String HttpResponse::getHeader(const String &value) {
    String key = value;
    transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c); });
    return headers.size() > 0 ? headers[key] : nullptr;
}

bool HttpResponse::containsHeader(const String &value) {
    for(HttpHeaders::iterator it = headers.begin(); it != headers.end(); ++it) {
        String key = value;
        transform(key.begin(), key.end(), key.begin(), [](unsigned char c){ return std::tolower(c); });
        if(key.compare(it->first) == 0) return true;
    }
    return false;
}