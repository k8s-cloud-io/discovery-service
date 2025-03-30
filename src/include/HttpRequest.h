#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <curl/curl.h>

#include "HttpHeader.h"
#include "HttpResponse.h"
#include "String.h"

class HttpRequest {
    public:
        enum RequestMethod {
            GET,
            POST,
            PUT,
            PATCH
        };

        HttpRequest(HttpRequest::RequestMethod, const String &);
        void setHeaders(const HttpHeaders &);
        void setHeader(const String &, const String &);

        HttpResponse *exec();
        RequestMethod getRequestMethod() const;
        String getUrl() const;

    private:
        HttpRequest();
        static std::size_t WriteCallback(void *, std::size_t, std::size_t, void *);

        RequestMethod requestMethod;
        String url;
        HttpHeaders headers;
};

#endif // HTTPREQUEST_H