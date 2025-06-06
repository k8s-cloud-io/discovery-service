#ifndef WEATHER_CONFIGURATION_H
#define WEATHER_CONFIGURATION_H

#include "WeatherProvider.h"

class WeatherConfiguration {
  public:
    explicit WeatherConfiguration(const WeatherProvider &provider = WeatherProvider());
    virtual ~WeatherConfiguration() = default;

    void setWeatherProvider(const WeatherProvider &);
    WeatherProvider getWeatherProvider() const;

  private:
    WeatherProvider provider;
};

#endif // WEATHER_CONFIGURATION_H