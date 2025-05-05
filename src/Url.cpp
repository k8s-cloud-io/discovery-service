#include "Url.h"

Url::Url()
:port(80){}

Url Url::parse(const String &s) {
    Url u;
    u.rawUrl = s;
    
    if(s.find("http://") == 0) {
        u.scheme = "http://";
    }

    if(s.find("https://") == 0) {
        u.scheme = "https://";
    }

    
    String host = s.substr(u.scheme.length());
    size_t firstSlash = host.find("/");
    if(firstSlash != String::npos) {
        host = host.substr(0, firstSlash);
    }

    size_t colonPos = host.find(":");
    if(colonPos != String::npos) {
        String hostPort = host.substr(colonPos+1);
        u.port = std::stoi(hostPort);
        host = host.substr(0, colonPos);
    }
    u.host = host;

    // parse path
    String path = s.substr(u.scheme.length());
    size_t pathStart = path.find("/");
    if(pathStart != String::npos) {
        path = path.substr(pathStart);
        size_t questionMark = path.find("?");
        if(questionMark != String::npos) {
            path = path.substr(0, questionMark);
        }
    } else {
        path = "/";
    }
    u.path = path;

    if(s.find("?") != String::npos) {
        String queryString = s.substr(s.find("?")+1);
        StringList parts = queryString.split("&");
        for(String part: parts) {
            size_t eq_pos = part.find("=");
            if(eq_pos != String::npos) {
                String key = part.substr(0, eq_pos);
                String val = part.substr(eq_pos+1);
                u.query[key] = val;
            }
        }
    }

    return u;
}

String Url::getScheme() const {
    return scheme;
}

String Url::getHost() const {
    return host;
}

int Url::getPort() const {
    return port;
}

String Url::getUser() const {
    return user;
}

String Url::getPassword() const {
    return password;
}

String Url::getPath() const {
    return path;
}

StringMap Url::getQuery() const {
    return query;
}

String Url::toString() const {
    return rawUrl;
}