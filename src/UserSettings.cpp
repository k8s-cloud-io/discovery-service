#include "UserSettings.h"

#include "File.h"
#include "User.h"
#include <iostream>

UserSettings::UserSettings()
:settingsFile("/etc/discovery-service/default.json") {
  User user = User::current();
  String filePath = user.getHomeDirectory().append("/.config/discovery-service/settings.json");
  if(File::exists(filePath)) {
    settingsFile = filePath;
  }

  if(!File::exists(settingsFile)) {
    std::cout << "unable to read settings file '" << settingsFile << "': file does not exist" << std::endl;
    exit(1);
  }
}

UserSettings::~UserSettings() {
}