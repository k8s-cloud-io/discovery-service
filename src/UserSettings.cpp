#include "UserSettings.h"

#include "File.h"
#include "User.h"
#include <iostream>

UserSettings::UserSettings()
:settingsFile("/etc/discovery-service/default.json") {
  User user = User::current();
  String localSettingsFile = user.getHomeDirectory().append("/.config/discovery-service/settings.json");
  if(File::exists(localSettingsFile)) {
    settingsFile = localSettingsFile;
  }

  if(!File::exists(settingsFile)) {
    std::cout << "unable to read settings file '" << settingsFile << "': file does not exist" << std::endl;
    exit(1);
  }

  if(!File::isReadable(settingsFile)) {
    std::cout << "unable to read settings file '" << settingsFile << "': file is not readable" << std::endl;
    exit(1);
  }

  String content = File(settingsFile).getBytes();
}

UserSettings::~UserSettings() {
}