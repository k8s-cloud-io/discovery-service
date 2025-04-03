#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "ByteArray.h"
#include "HttpHeader.h"
#include "String.h"

class HttpRequest;

class HttpResponse {
    public:
    unsigned int getStatusCode() const;
        ByteArray getBody() const;
        HttpHeaders getHeaders();
        String getHeader(const String &);
        bool containsHeader(const String &);

    private:
        friend class HttpRequest;
        HttpResponse();

        unsigned int statusCode;
        ByteArray body;
        HttpHeaders headers;
};

#endif // HTTPRESPONSE_H