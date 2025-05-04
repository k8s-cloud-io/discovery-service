#include "json/value.h"
#include <json/json.h>
#include "File.h"
#include "Location.h"
#include "Logger.h"
#include "User.h"
#include "weather/OpenWeatherMapProvider.h"
#include "weather/WorldWeatherOnlineProvider.h"
#include "UserSettings.h"

UserSettings::UserSettings()
  : settingsFile("/etc/discovery-service/default.json") {
  const User user = User::current();
  if (const String localSettingsFile = user.getHomeDirectory().append("/.config/discovery-service/settings.json");
    File::exists(localSettingsFile)) {
    settingsFile = localSettingsFile;
  }

  if (!File::exists(settingsFile)) {
    Logger::log("unable to read settings file '" + settingsFile + "': file does not exist");
    ::exit(1);
  }

  if (!File::isReadable(settingsFile)) {
    Logger::log("unable to read settings file '" + settingsFile + "': file is not readable");
    ::exit(1);
  }

  String content = File(settingsFile).getBytes();
  content = content.trim();

  Json::Value root;
  Json::Reader reader;
  reader.parse(content, root);

  feeds.clear();

  if (const Json::Value feedsJson = root["feeds"]; feedsJson.isArray()) {
    for (const auto &i: feedsJson) {
      if (i.isString()) {
        feeds.emplace_back(i.asString());
      }
    }
  }

  const Json::Value weatherJson = root["weather"];
  if (weatherJson.isObject()) {
    String providerType;
    Json::Value providerJson = weatherJson["provider"];

    if (providerJson.isObject()) {
      Credentials credentials;

      if (providerJson["type"].isString()) {
        providerType = providerJson["type"].asString();
      }

      if (providerType.empty()) {
        Logger::log("configuration error: weather provider type is empty");
        ::exit(1);
      }

      if (providerJson["credentials"].isObject()) {
        Json::Value credentialsJson = providerJson["credentials"];
        auto names = credentialsJson.getMemberNames();
        StringMap credentialsMap;
        for (const auto &i: names) {
          if (credentialsJson[i].isString()) {
            credentialsMap[i] = credentialsJson[i].asString();
          }
        }

        if (credentialsMap.contains("apiKey")) {
          credentials.setApiKey(credentialsMap["apiKey"]);
        }

        if (credentialsMap.contains("userName")) {
          credentials.setUserName(credentialsMap["userName"]);
        }

        if (credentialsMap.contains("password")) {
          credentials.setPassword(credentialsMap["password"]);
        }
      }

      if (providerType.compare("WORLD_WEATHER_ONLINE") == 0) {
        weatherProvider = new WorldWeatherOnlineProvider();
        weatherProvider->setCredentials(credentials);
      }

      if (providerType.compare("OPEN_WEATHER_MAP") == 0) {
        weatherProvider = new OpenWeatherMapProvider();
        weatherProvider->setCredentials(credentials);
      }

      if (weatherProvider == nullptr) {
          Logger::log("Unable to load weather: invalid provider configuration");
          ::exit(1);
      }

      if(providerJson["location"].isObject()) {
        Location location;
        Json::Value locationJson = providerJson["location"];
        String latitude;
        String longitude;
        String city;
        String country;
        String state;

        if(locationJson["latitude"].isObject()) {
          latitude = locationJson.get("latitude", "").asString();
          location.setLatitude(latitude);
        }
        if(locationJson["longitude"].isObject()) {
          longitude = locationJson.get("longitude", "").asString();
          location.setLongitude(longitude);
        }
        if(locationJson["city"].isObject()) {
          city = locationJson.get("city", "").asString();
          location.setCity(city);
        }
        if(locationJson["country"].isObject()) {
          country = locationJson.get("country", "").asString();
          location.setCountry(country);
        }
        if(locationJson["state"].isObject()) {
          state = locationJson.get("state", "").asString();
          location.setState(state);
        }

        weatherProvider->setLocation(location);
      }
    }
  }
}

UserSettings::~UserSettings() {
}

StringList UserSettings::getFeeds() const {
  return feeds;
}

WeatherProvider *UserSettings::getWeatherProvider() const {
  return weatherProvider;
}