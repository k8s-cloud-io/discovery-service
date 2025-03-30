#include "Dir.h"
#include "File.h"

#include <filesystem>
namespace fs = std::filesystem;

File::File(const string &p)
:path(p) {}

string File::getDirectory() {
    if(File::isDirectory(path)) {
        return path;
    }

    const size_t pos = path.rfind('/');
    if(pos != string::npos) {
        return path.substr(0, pos);
    }

    return Dir::currentDir();
}

string File::getAbsolutePath() const {
    string p = path;
    size_t pos = path.find("./");
    if(pos != string::npos && pos == 0) {
        p = path.substr(2);
    }
    
    return fs::absolute(p);
}

bool File::exists(const string &path) {
    return fs::exists(path);
}

bool File::isDirectory(const string &path) {
    return fs::is_directory(path);
}

// private
File::File(){}