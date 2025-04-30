#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include "String.h"
#include "StringList.h"
#include "WeatherProvider.h"

class UserSettings {
  public:
    UserSettings();
    virtual ~UserSettings();

    [[nodiscard]] StringList getFeeds() const;
    WeatherProvider getWeatherProvider() const;

  private:
    String settingsFile;
    StringList feeds;
    WeatherProvider weatherProvider;
};

#endif //USER_SETTINGS_H
