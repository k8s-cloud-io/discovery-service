#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include "String.h"
#include "StringList.h"

class UserSettings {
  public:
    UserSettings();
    ~UserSettings();

    [[nodiscard]] StringList getFeeds() const;

  private:
    String settingsFile;
    StringList feeds;
};

#endif //USER_SETTINGS_H
