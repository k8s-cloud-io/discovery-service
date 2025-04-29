#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "ByteArray.h"
#include "HttpHeader.h"
#include "String.h"

class HttpRequest;

class HttpResponse {
    public:
    [[nodiscard]] unsigned int getStatusCode() const;
        [[nodiscard]] ByteArray getBody() const;
        HttpHeaders getHeaders() const;
        String getHeader(const String &) const;
        [[nodiscard]] bool containsHeader(const String &) const;

    private:
        friend class HttpRequest;
        HttpResponse();

        unsigned int statusCode;
        ByteArray body;
        HttpHeaders headers;
};

#endif // HTTP_RESPONSE_H