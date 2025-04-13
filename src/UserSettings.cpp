#include "UserSettings.h"

#include "File.h"
#include "User.h"
#include <iostream>
#include <json/json.h>

UserSettings::UserSettings()
  : settingsFile("/etc/discovery-service/default.json") {
  const User user = User::current();
  if (const String localSettingsFile = user.getHomeDirectory().append("/.config/discovery-service/settings.json");
    File::exists(localSettingsFile)) {
    settingsFile = localSettingsFile;
  }

  if (!File::exists(settingsFile)) {
    std::cout << "unable to read settings file '" << settingsFile << "': file does not exist" << std::endl;
    exit(1);
  }

  if (!File::isReadable(settingsFile)) {
    std::cout << "unable to read settings file '" << settingsFile << "': file is not readable" << std::endl;
    exit(1);
  }

  String content = File(settingsFile).getBytes();
  content = content.trim();

  Json::Value root;
  Json::Reader reader;
  reader.parse(content, root);

  weatherConfiguration.setWeatherProvider(WeatherProvider());
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
      Credentials credentials = Credentials::CREDENTIALS_TYPE_NONE;

      if (providerJson["type"].isString()) {
        providerType = providerJson["type"].asString();
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
          credentials = Credentials::CREDENTIALS_TYPE_API_KEY;
          credentials.setApiKey(credentialsMap["apiKey"]);
        }

        if (credentialsMap.contains("userName") && credentialsMap.contains("password")) {
          credentials = Credentials::CREDENTIALS_TYPE_USER;
          credentials.setUserName(credentialsMap["userName"]);
          credentials.setPassword(credentialsMap["password"]);
        }
      }

      if (providerType.empty()) {
        std::cout << "configuration error: weather provider type is empty" << std::endl;
        exit(1);
      }

      if (providerType.compare("WORLD_WEATHER_ONLINE") == 0) {
        if (credentials.getApiKey().empty()) {
          std::cout << "configuration error: weather provider api key for provider WORLD_WEATHER_ONLINE is empty" << std::endl;
        }
        auto provider = WeatherProvider(WeatherProvider::PROVIDER_WORLD_WEATHER_ONLINE);
        provider.setCredentials(credentials);
        weatherConfiguration.setWeatherProvider(provider);
      }
    }
  }
}

UserSettings::~UserSettings() {
}

StringList UserSettings::getFeeds() const {
  return feeds;
}