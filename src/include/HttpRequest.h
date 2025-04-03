#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

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
        static std::size_t WriteCallback(const void *, std::size_t, std::size_t, void *);

        RequestMethod requestMethod;
        String url;
        HttpHeaders headers;
};

#endif // HTTPREQUEST_H