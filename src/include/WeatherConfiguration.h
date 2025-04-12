#ifndef WEATHER_CONFIGURATION_H
#define WEATHER_CONFIGURATION_H

#include "WeatherProvider.h"

class WeatherConfiguration {
  public:
    WeatherConfiguration(const WeatherProvider &);
    WeatherProvider getWeatherProvider() const;

  private:
    WeatherProvider provider;
};

#endif // WEATHER_CONFIGURATION_H