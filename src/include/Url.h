#ifndef URL_H
#define URL_H

#include "String.h"
#include "StringMap.h"

class Url {
    public:
        Url();
        virtual ~Url() = default;
        static Url parse(const String &);

        String getScheme() const;
        String getHost() const;
        String getUser() const;
        String getPassword() const;
        String getPath() const;
        String toString() const;

        StringMap getQuery() const;
        int getPort() const;

    private:
    String rawUrl;
        String scheme;
        String host;
        String user;
        String password;
        String path;
        StringMap query;
        int port;

};

#endif // URL_H