#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include "String.h"

class UserSettings {
  public:
    UserSettings();
    ~UserSettings();

  private:
    String settingsFile;
};

#endif //USER_SETTINGS_H
