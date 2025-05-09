#ifndef CINNAMON_DISCOVERY_H
#define CINNAMON_DISCOVERY_H

#include "Application.h"
#include "SqlDatabase.h"
#include "CinnamonWebService.h"

class CinnamonDiscovery: public Application {
    public:
        CinnamonDiscovery();
        virtual ~CinnamonDiscovery();

        void init();
        static SqlDatabase getDatabase();

    private:
    CinnamonWebService *webService;
        static SqlDatabase database;
};

#endif