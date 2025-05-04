#ifndef WORLD_WEATHER_ONLINE_PROVIDER_H
#define WORLD_WEATHER_ONLINE_PROVIDER_H

#include "WeatherProvider.h"

class WorldWeatherOnlineProvider: public WeatherProvider {
    public:
        WorldWeatherOnlineProvider() = default;
        virtual ~WorldWeatherOnlineProvider() = default;

        virtual void load() const override;
};

#endif // WORLD_WEATHER_ONLINE_PROVIDER_H