#include <algorithm>
#include <cctype>
#include <curl/curl.h>
#include <iostream>

#include "HttpRequest.h"
#include "CharBuffer.h"

using std::cout;
using std::endl;
using std::vector;
using std::transform;
using std::tolower;

HttpRequest::HttpRequest(HttpRequest::RequestMethod m, const String &u)
    :requestMethod(m), url(u) {
}

HttpRequest::RequestMethod HttpRequest::getRequestMethod() const {
    return requestMethod;
}

String HttpRequest::getUrl() const {
    return url;
}

HttpResponse *HttpRequest::exec() {
    CURL *curl;
    CURLcode res;
    CharBuffer buffer;
    HttpResponse *response = new HttpResponse();

    curl = curl_easy_init();
    if(curl != nullptr) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &HttpRequest::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 2000L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cout << "CURL ERROR: " << curl_easy_strerror(res) << endl;
        } else {
            response->body = buffer;

            int http_code;
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
            response->statusCode = http_code;

            struct curl_header *h;
            struct curl_header *prev = nullptr;
            do {
                h = curl_easy_nextheader(curl, CURLH_HEADER, -1, prev);

                if(h) {
                    String header = h->name;
                    transform(header.begin(), header.end(), header.begin(),
                        [](unsigned char c){ return std::tolower(c); });
                    response->headers[header] = h->value;
                }
                prev = h;
            } while(h);
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
std::size_t HttpRequest::WriteCallback(void *contents, std::size_t size, std::size_t nmemb, void *userp) {
    std::size_t realSize = size * nmemb;
    const char *data = reinterpret_cast<const char *>(contents);
    for(std::size_t index = 0; index < realSize; index++) {
        ((CharBuffer *)userp)->push_back(data[index]);
    }
    return realSize;
}

HttpRequest::HttpRequest() {}