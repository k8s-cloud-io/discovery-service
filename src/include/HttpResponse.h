#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "CharBuffer.h"
#include "HttpHeader.h"
#include "String.h"

class HttpRequest;

class HttpResponse {
    public:
    unsigned int getStatusCode() const;
        CharBuffer getBody() const;
        HttpHeaders getHeaders();
        String getHeader(const String &);
        bool containsHeader(const String &);

    private:
        friend class HttpRequest;
        HttpResponse();

        unsigned int statusCode;
        CharBuffer body;
        HttpHeaders headers;
};

#endif // HTTPRESPONSE_H