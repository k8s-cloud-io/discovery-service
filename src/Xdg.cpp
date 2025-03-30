#include <fstream>
#include <iostream>

#include "File.h"
#include "String.h"
#include "Xdg.h"

using std::ifstream;
using std::cout;
using std::endl;

bool Xdg::initialized = false;
Xdg::XdgMap Xdg::config;

Xdg::Xdg(){
}

string Xdg::getDirectory(const Xdg::XdgDirectory &directory){
    Xdg::loadConfig();
    return config[directory];
}

void Xdg::loadConfig() {
    if(!Xdg::initialized) {
        const char *home = std::getenv("HOME");
        if(home) {
            string configPath = string(home).append("/.config");
            if(File::isDirectory(configPath)) {
                string xdgFile = configPath.append("/user-dirs.dirs");
                if(File::exists(xdgFile)) {
                    ifstream file(xdgFile);
                    string str;

                    while (std::getline(file, str)) {
                        string line = String::trim(str);
                        if(line.length() == 0 || line.find("#") == 0 || line.find("=") == string::npos) continue;
                        size_t equalPosition = line.find("=");
                        
                        string keyPart = line.substr(0, equalPosition);
                        string valPart = line.substr(equalPosition + 1);

                        string key = String::trim(keyPart);
                        string val = String::trim(valPart);
                        
                        while(val.at(0) == '"') {
                            val = val.substr(1);
                        }

                        while(val.at(val.length() -1) == '"') {
                            val = val.substr(0, val.length() - 1);
                        }

                        StringList pathParts = String::split(val, "/");
                        for(string part: pathParts) {
                            if(part.at(0) == '$') {
                                string origin = part;
                                part = part.substr(1);
                                string env = std::getenv(part.c_str());
                                size_t envStart = val.find(part);
                                val = val.replace(envStart-1, part.length()+1, env);
                            }
                        }

                        XdgDirectory xdgDir;
                        if(key.compare("XDG_DESKTOP_DIR") == 0) {
                            xdgDir = Xdg::XDG_DESKTOP_DIR;
                        }
                        if(key.compare("XDG_DOWNLOAD_DIR") == 0) {
                            xdgDir = Xdg::XDG_DOWNLOAD_DIR;
                        }
                        if(key.compare("XDG_TEMPLATES_DIR") == 0) {
                            xdgDir = Xdg::XDG_TEMPLATES_DIR;
                        }
                        if(key.compare("XDG_PUBLICSHARE_DIR") == 0) {
                            xdgDir = Xdg::XDG_PUBLICSHARE_DIR;
                        }
                        if(key.compare("XDG_DOCUMENTS_DIR") == 0) {
                            xdgDir = Xdg::XDG_DOCUMENTS_DIR;
                        }
                        if(key.compare("XDG_MUSIC_DIR") == 0) {
                            xdgDir = Xdg::XDG_MUSIC_DIR;
                        }
                        if(key.compare("XDG_PICTURES_DIR") == 0) {
                            xdgDir = Xdg::XDG_PICTURES_DIR;
                        }
                        if(key.compare("XDG_VIDEOS_DIR") == 0) {
                            xdgDir = Xdg::XDG_VIDEOS_DIR;
                        }

                        if(xdgDir != Xdg::XDG_UNKNOWN)
                            config[xdgDir] = val;
                    }
                }
            }
        }

        Xdg::initialized = true;
    }
}
