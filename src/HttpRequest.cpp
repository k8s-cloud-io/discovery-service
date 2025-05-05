#include <algorithm>
#include <cctype>
#include <cstddef>
#include <curl/urlapi.h>
#include <iostream>
#include <curl/curl.h>
#include "ByteArray.h"
#include "HttpRequest.h"

HttpRequest::HttpRequest(const RequestMethod m, Url u)
    :requestMethod(m), url(u) {
}

HttpRequest::HttpRequest(const RequestMethod m, const String &u)
    :requestMethod(m), url(Url::parse(u)) {
}

HttpRequest::RequestMethod HttpRequest::getRequestMethod() const {
    return requestMethod;
}

Url HttpRequest::getUrl() const {
    return url;
}

HttpResponse *HttpRequest::exec() const {
    ByteArray buffer;
    auto response = new HttpResponse();

    if(auto curl = curl_easy_init(); curl != nullptr) {
        String scheme = url.getScheme();
        String host = url.getHost();
        String path = url.getPath();
        int port = url.getPort();

        String baseUri = String("%1%2%3").arg(3, scheme.c_str(), host.c_str(), path.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, baseUri.c_str());

        if(!url.getQuery().empty()) {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
            CURLU* curlu = curl_url();
            curl_url_set(curlu, CURLUPART_SCHEME, url.getScheme().c_str(), 0);

            for(const auto &[key, val] : url.getQuery()) {
                String query = String("%1=%2").arg(2, key.c_str(), val.c_str());
                curl_url_set(curlu, CURLUPART_QUERY, query.c_str(), CURLU_APPENDQUERY | CURLU_URLENCODE);
            }
            curl_url_set(curlu, CURLUPART_URL, url.toString().c_str(), 0);

            if(port != 80) {
                curl_url_set(curlu, CURLUPART_PORT, String::valueOf(port).c_str(), 0);
            }
            curl_easy_setopt(curl, CURLOPT_CURLU, curlu);
        } else {
            if(port != 80) {
                curl_easy_setopt(curl, CURLOPT_PORT, port);
            }
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HttpRequest::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 2000L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
#ifdef DEBUG
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif

        if(const CURLcode res = curl_easy_perform(curl); res == CURLE_OK) {
            int http_code;
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
            response->statusCode = http_code;
            response->body = buffer;

            curl_header *h;
            curl_header *prev = nullptr;
            do {
                h = curl_easy_nextheader(curl, CURLH_HEADER, -1, prev);

                if(h) {
                    String header = h->name;
                    std::transform(header.begin(), header.end(), header.begin(),
                        [](unsigned char c){ return ::tolower(c); });
                    response->headers[header] = h->value;
                }
                prev = h;
            } while(h);
        } else {
            String error = curl_easy_strerror(res);
            std::cout << "ERROR IN HttpRequest: " << error << std::endl;
        }
        curl_easy_cleanup(curl);
    }

    return response;
}

void HttpRequest::setHeaders(const HttpHeaders &h) {
    headers = h;
};

void HttpRequest::setHeader(const String &k, const String &v) {
    headers[k] = v;
}

// private
::size_t HttpRequest::WriteCallback(const void *contents, std::size_t size, std::size_t nmemb, void *userp) {
    if(contents == nullptr) {
        return 0;
    }

    const ::size_t realSize = size * nmemb;
    auto data = static_cast<const unsigned char *>(contents);

    for(std::size_t index = 0; index < realSize; index++) {
        static_cast<ByteArray *>(userp)->push_back(data[index]);
    }
    return realSize;
}

HttpRequest::HttpRequest()
    :requestMethod(UNKNOWN){}