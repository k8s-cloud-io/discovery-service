//
// Created by andreas on 05.04.25.
//

#include "User.h"
#include "Xdg.h"
#include <pwd.h>
#include <unistd.h>

#include <cstring>

User::User(const int id) {
    if(id == -1) {
      this->id = geteuid ();
    } else {
      this->id = id;
    }
}

User User::current() {
  return User();
}

int User::getId() const {
  return id;
}

String User::getName() const {
  return getpwuid(this->id)->pw_name;
}

String User::getHomeDirectory() const {
  String home = getpwuid(this->id)->pw_dir;
  if(home.size() == 0) {
    home = getenv("HOME");
  }
  return home;
}

String User::getDirectory(const XdgDirectory dir) const {
  const String home = getHomeDirectory();
  const String xdgFile = getHomeDirectory() + "/.config/user-dirs.dirs";
  XdgMap map = Xdg::loadConfig(xdgFile);
  String path = map[dir];
  if(path.find("$HOME") == 0) {
    path = path.substr(std::strlen("$HOME")+1);
  }

  return home + "/" + path;
}