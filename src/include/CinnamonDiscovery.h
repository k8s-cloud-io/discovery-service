#ifndef CINNAMON_DISCOVERY_H
#define CINNAMON_DISCOVERY_H

#include "Application.h"
#include "SqlDatabase.h"

class CinnamonDiscovery: public Application {
    public:
        void init();
        static SqlDatabase getDatabase();

    private:
        static SqlDatabase database;
};

#endif