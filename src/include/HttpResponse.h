#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "CharBuffer.h"
#include "HttpHeader.h"

class HttpRequest;

class HttpResponse {
    public:
    unsigned int getStatusCode() const;
        CharBuffer getBody() const;
        HttpHeaders getHeaders();
        string getHeader(const string &);
        bool containsHeader(const string &);

    private:
        friend class HttpRequest;
        HttpResponse();

        unsigned int statusCode;
        CharBuffer body;
        HttpHeaders headers;
};

#endif // HTTPRESPONSE_H