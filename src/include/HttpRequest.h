#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "HttpHeader.h"
#include "HttpResponse.h"
#include "String.h"
#include "Url.h"

class HttpRequest {
    public:
        enum RequestMethod {
            UNKNOWN = 0,
            GET,
            POST,
            PUT,
            PATCH
        };

        HttpRequest(RequestMethod, const String &);
        HttpRequest(RequestMethod, Url);
        virtual ~HttpRequest() = default;

        void setHeaders(const HttpHeaders &);
        void setHeader(const String &, const String &);

        [[nodiscard]] HttpResponse *exec() const;
        [[nodiscard]] RequestMethod getRequestMethod() const;
        [[nodiscard]] Url getUrl() const;

    private:
        HttpRequest();
        static ::size_t WriteCallback(const void *, ::size_t, ::size_t, void *);

        RequestMethod requestMethod;
        Url url;
        HttpHeaders headers;
};

#endif // HTTP_REQUEST_H