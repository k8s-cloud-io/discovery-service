#ifndef XDG_H
#define XDG_H

#include <map>
using std::map;

#include "StringMap.h"

enum XdgDirectory {
    XDG_UNKNOWN = 0,
    XDG_DOCUMENTS_DIR,
    XDG_PICTURES_DIR,
    XDG_DOWNLOAD_DIR,
    XDG_TEMPLATES_DIR,
    XDG_VIDEOS_DIR,
    XDG_DESKTOP_DIR,
    XDG_MUSIC_DIR,
    XDG_PUBLIC_SHARE_DIR
};
typedef map<XdgDirectory, String> XdgMap;

class Xdg final {
    public:
        static XdgMap loadConfig(const String &);
};

#endif // XDG_H