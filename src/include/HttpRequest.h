#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <curl/curl.h>

#include "HttpHeader.h"
#include "HttpResponse.h"

using std::string;

class HttpRequest {
    public:
        enum RequestMethod {
            GET,
            POST,
            PUT,
            PATCH
        };

        HttpRequest(HttpRequest::RequestMethod, const string &);
        void setHeaders(HttpHeaders);
        void setHeader(const string &, const string &);

        HttpResponse *exec();
        RequestMethod getRequestMethod() const;
        string getUrl() const;

    private:
        HttpRequest();
        static size_t WriteCallback(void *, size_t, size_t, void *);

        RequestMethod requestMethod;
        string url;
        HttpHeaders headers;
};

#endif // HTTPREQUEST_H