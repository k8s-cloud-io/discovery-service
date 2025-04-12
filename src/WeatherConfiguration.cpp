#include "WeatherConfiguration.h"

WeatherConfiguration::WeatherConfiguration(const WeatherProvider &provider)
:provider(provider) {}

WeatherProvider WeatherConfiguration::getWeatherProvider() const {
  return provider;
}