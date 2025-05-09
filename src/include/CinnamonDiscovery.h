#ifndef CINNAMON_DISCOVERY_H
#define CINNAMON_DISCOVERY_H

#include "Application.h"
#include "SqlDatabase.h"
#include "WebService.h"

class CinnamonDiscovery: public Application {
    public:
        CinnamonDiscovery();
        virtual ~CinnamonDiscovery();
        
        void init();
        static SqlDatabase getDatabase();

    private:
        WebService *webService;
        static SqlDatabase database;
};

#endif