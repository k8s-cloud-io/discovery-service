#include <fstream>

#include "File.h"
#include "Xdg.h"

#include <Exception.h>
#include <unistd.h>

using std::ifstream;

XdgMap Xdg::loadConfig(const String &configPath) {
    String xdgFile;
    XdgMap config;
    bool defaults = false;

    if (File::exists(configPath)) {
        xdgFile = configPath;
    }

    if (xdgFile.empty()) {
        xdgFile = "/etc/xdg/user-dirs.defaults";
        defaults = true;
    }

    if (!File::exists(xdgFile)) {
        throw Exception("Xdg config file does not exist");
    }

    ifstream file(xdgFile);
    String str;

    while (std::getline(file, str)) {
        String line = str.trim();
        if(line.empty() || line.find("#") == 0 || line.find("=") == string::npos) continue;
        std::size_t equalPosition = line.find("=");

        String keyPart = line.substr(0, equalPosition);
        String valPart = line.substr(equalPosition + 1);

        String key = keyPart.trim();
        String val = valPart.trim();

        while(val.at(0) == '"') {
            val = val.substr(1);
        }

        while(val.at(val.length() -1) == '"') {
            val = val.substr(0, val.length() - 1);
        }

        XdgDirectory xdgDir;
        if(key == "XDG_DESKTOP_DIR" || (defaults && key == "DESKTOP")) {
            xdgDir = XDG_DESKTOP_DIR;
        }
        if(key == "XDG_DOWNLOAD_DIR"  || (defaults && key == "DOWNLOAD")) {
            xdgDir = XDG_DOWNLOAD_DIR;
        }
        if(key == "XDG_TEMPLATES_DIR" || (defaults && key == "TEMPLATES")) {
            xdgDir = XDG_TEMPLATES_DIR;
        }
        if(key == "XDG_PUBLICSHARE_DIR" || (defaults && key == "PUBLICSHARE")) {
            xdgDir = XDG_PUBLIC_SHARE_DIR;
        }
        if(key == "XDG_DOCUMENTS_DIR" || (defaults && key == "DOCUMENTS")) {
            xdgDir = XDG_DOCUMENTS_DIR;
        }
        if(key == "XDG_MUSIC_DIR" || (defaults && key == "MUSIC")) {
            xdgDir = XDG_MUSIC_DIR;
        }
        if(key == "XDG_PICTURES_DIR" || (defaults && key == "PICTURES")) {
            xdgDir = XDG_PICTURES_DIR;
        }
        if(key == "XDG_VIDEOS_DIR" || (defaults && key == "VIDEOS")) {
            xdgDir = XDG_VIDEOS_DIR;
        }

        if(xdgDir != XDG_UNKNOWN)
            config[xdgDir] = val;

        if (!config.contains(XDG_RUNTIME_DIR)) {
            String runtimeDir = getenv("XDG_RUNTIME_DIR");
            if (runtimeDir.empty()) {
                int uid = getuid();
                String uidStr = std::to_string(uid);
                runtimeDir = "/run/user/" + uidStr;
            }
            config[XDG_RUNTIME_DIR] = runtimeDir;
        }
    }
    return config;
}
