#include <cstring>
#include <pwd.h>
#include <unistd.h>
#include "User.h"
#include "Xdg.h"

User::User(const int id) {
    if(id == -1) {
      this->uid = geteuid ();
    } else {
      this->uid = id;
    }
}

User User::current() {
  return User();
}

int User::getUid() const {
  return uid;
}

String User::getName() const {
  return getpwuid(this->uid)->pw_name;
}

String User::getHomeDirectory() const {
  String home = getpwuid(this->uid)->pw_dir;
  if(home.size() == 0) {
    home = getenv("HOME");
  }
  return home;
}

String User::getDirectory(const XdgDirectory dir) const {
  const String home = getHomeDirectory();
  const String xdgFile = getHomeDirectory() + "/.config/user-dirs.dirs";
  XdgMap map = Xdg::loadConfig(xdgFile);
  if (dir == XDG_RUNTIME_DIR) return map[dir];

  String path = map[dir];
  if(path.find("$HOME") == 0) {
    path = path.substr(std::strlen("$HOME")+1);
  }

  return home + "/" + path;
}