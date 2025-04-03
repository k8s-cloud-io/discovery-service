#include <fstream>
#include <iostream>

#include "File.h"
#include "StringList.h"
#include "Xdg.h"

using std::ifstream;
using std::cout;
using std::endl;

bool Xdg::initialized = false;
Xdg::XdgMap Xdg::config;

Xdg::Xdg()= default;

String Xdg::getDirectory(const XdgDirectory &directory){
    Xdg::loadConfig();
    return config[directory];
}

void Xdg::loadConfig() {
    if(!initialized) {
        if(const char *home = std::getenv("HOME")) {
            if(const String configPath = string(home).append("/.config"); File::isDirectory(configPath)) {
                if(const String xdgFile = configPath.append("/user-dirs.dirs"); File::exists(xdgFile)) {
                    ifstream file(xdgFile);
                    String str;

                    while (std::getline(file, str)) {
                        String line = str.trim();
                        if(line.length() == 0 || line.find("#") == 0 || line.find("=") == string::npos) continue;
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

                        StringList pathParts = val.split("/");
                        for(string part: pathParts) {
                            if(part.at(0) == '$') {
                                string origin = part;
                                part = part.substr(1);
                                string env = std::getenv(part.c_str());
                                std::size_t envStart = val.find(part);
                                val = val.replace(envStart-1, part.length()+1, env);
                            }
                        }

                        XdgDirectory xdgDir;
                        if(key == "XDG_DESKTOP_DIR") {
                            xdgDir = XDG_DESKTOP_DIR;
                        }
                        if(key == "XDG_DOWNLOAD_DIR") {
                            xdgDir = XDG_DOWNLOAD_DIR;
                        }
                        if(key == "XDG_TEMPLATES_DIR") {
                            xdgDir = XDG_TEMPLATES_DIR;
                        }
                        if(key == "XDG_PUBLICSHARE_DIR") {
                            xdgDir = XDG_PUBLIC_SHARE_DIR;
                        }
                        if(key == "XDG_DOCUMENTS_DIR") {
                            xdgDir = XDG_DOCUMENTS_DIR;
                        }
                        if(key == "XDG_MUSIC_DIR") {
                            xdgDir = XDG_MUSIC_DIR;
                        }
                        if(key == "XDG_PICTURES_DIR") {
                            xdgDir = XDG_PICTURES_DIR;
                        }
                        if(key == "XDG_VIDEOS_DIR") {
                            xdgDir = XDG_VIDEOS_DIR;
                        }

                        if(xdgDir != XDG_UNKNOWN)
                            config[xdgDir] = val;
                    }
                }
            }
        }

        Xdg::initialized = true;
    }
}
