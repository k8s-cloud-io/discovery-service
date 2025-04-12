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

  feeds.clear();
  if (const Json::Value feedList = root["feeds"]; feedList.isArray()) {
    for (const auto &i: feedList) {
      if (i.isString()) {
        feeds.emplace_back(i.asString());
      }
    }
  }
  std::cout << "feeds size: " << feeds.size() << std::endl;
}

UserSettings::~UserSettings() {
}

StringList UserSettings::getFeeds() const {
  return feeds;
}