#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "HttpHeader.h"
#include "HttpResponse.h"
#include "String.h"

class HttpRequest {
    public:
        enum RequestMethod {
            UNKNOWN = 0,
            GET,
            POST,
            PUT,
            PATCH
        };

        HttpRequest(RequestMethod, String );
        void setHeaders(const HttpHeaders &);
        void setHeader(const String &, const String &);

        [[nodiscard]] HttpResponse *exec() const;
        [[nodiscard]] RequestMethod getRequestMethod() const;
        [[nodiscard]] String getUrl() const;

    private:
        HttpRequest();
        static ::size_t WriteCallback(const void *, ::size_t, ::size_t, void *);

        RequestMethod requestMethod;
        String url;
        HttpHeaders headers;
};

#endif // HTTP_REQUEST_H