#ifndef XDG_H
#define XDG_H

#include <map>
#include <string>
using std::string;
using std::map;

#include "StringMap.h"

class Xdg {
    public:
        enum XdgDirectory {
            XDG_UNKNOWN = 0,
            XDG_DOCUMENTS_DIR,
            XDG_PICTURES_DIR,
            XDG_DOWNLOAD_DIR,
            XDG_TEMPLATES_DIR,
            XDG_VIDEOS_DIR,
            XDG_DESKTOP_DIR,
            XDG_MUSIC_DIR,
            XDG_PUBLICSHARE_DIR
        };
        virtual ~Xdg(){}
        static string getDirectory(const XdgDirectory &);

    private:
        Xdg();
        typedef map<Xdg::XdgDirectory, string> XdgMap;
        static bool initialized;
        static XdgMap config;
        static void loadConfig();
};

#endif // XDG_H