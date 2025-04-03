#include "Dir.h"
#include "File.h"

#include <filesystem>
#include <utility>
namespace fs = std::filesystem;

File::File(String p)
:path(std::move(p)) {}

String File::getDirectory() {
    if(File::isDirectory(path)) {
        return path;
    }

    if(const std::size_t pos = path.rfind('/'); pos != string::npos) {
        return String(path.substr(0, pos));
    }

    return Dir::currentDir();
}

String File::getAbsolutePath() const {
    string p = path;
    if(const std::size_t pos = path.find("./"); pos != String::npos && pos == 0) {
        p = path.substr(2);
    }
    
    return static_cast<String>(fs::absolute(p.c_str()));
}

bool File::exists(const String &path) {
    return fs::exists(path.c_str());
}

bool File::isDirectory(const String &path) {
    return fs::is_directory(path.c_str());
}

// private
File::File() = default;