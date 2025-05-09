#ifndef CINNAMON_WEB_SERVICE_H
#define CINNAMON_WEB_SERVICE_H

#include "String.h"
#include "UnixSocket.h"

class CinnamonWebService {
public:
    CinnamonWebService();
    virtual ~CinnamonWebService();

    void start();
    void stop();

    private:
        static UnixSocket *socket;
        String socketPath;
};

#endif // CINNAMON_WEB_SERVICE_H