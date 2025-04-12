#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include <WeatherConfiguration.h>

#include "String.h"
#include "StringList.h"

class UserSettings {
  public:
    UserSettings();
    ~UserSettings();

    [[nodiscard]] StringList getFeeds() const;
    WeatherConfiguration getWeatherConfiguraton() const;

  private:
    String settingsFile;
    StringList feeds;
    WeatherConfiguration weatherConfiguration;
};

#endif //USER_SETTINGS_H
