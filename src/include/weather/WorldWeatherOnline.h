#ifndef WORLD_WEATHER_ONLINE_H
#define WORLD_WEATHER_ONLINE_H

#include "Credentials.h"

class WorldWeatherOnline {
    public:
        WorldWeatherOnline();

        void setCredentials(const Credentials &);

    private:
        Credentials credentials;
};

#endif // WORLD_WEATHER_ONLINE_H