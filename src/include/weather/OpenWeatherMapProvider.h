#ifndef OPEN_WEATHER_MAP_PROVIDER
#define OPEN_WEATHER_MAP_PROVIDER

#include "WeatherProvider.h"

class OpenWeatherMapProvider: public WeatherProvider {
    public:
        OpenWeatherMapProvider() = default;
        virtual ~OpenWeatherMapProvider() = default;

        virtual void load() const override;
};

#endif // OPEN_WEATHER_MAP_PROVIDER