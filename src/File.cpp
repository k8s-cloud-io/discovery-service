#include "Dir.h"
#include "File.h"

#include <filesystem>
namespace fs = std::filesystem;

File::File(const String &p)
:path(p) {}

String File::getDirectory() {
    if(File::isDirectory(path)) {
        return path;
    }

    const std::size_t pos = path.rfind('/');
    if(pos != string::npos) {
        return path.substr(0, pos);
    }

    return Dir::currentDir();
}

String File::getAbsolutePath() const {
    String p = path;
    std::size_t pos = path.find("./");
    if(pos != String::npos && pos == 0) {
        p = path.substr(2);
    }
    
    return (String)fs::absolute(p.c_str());
}

bool File::exists(const String &path) {
    return fs::exists(path.c_str());
}

bool File::isDirectory(const String &path) {
    return fs::is_directory(path.c_str());
}

// private
File::File(){}