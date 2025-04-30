#include <filesystem>
#include <fstream>
#include <unistd.h>
#include "Dir.h"
#include "File.h"
namespace fs = std::filesystem;

File::File(String p)
:path(p) {}

String File::getDirectory() {
    if(isDirectory(path)) {
        return path;
    }

    if(const std::size_t pos = path.rfind('/'); pos != String::npos) {
        return path.substr(0, pos);
    }

    return Dir::currentDir();
}

String File::getAbsolutePath() const {
    String p = path;
    if(const std::size_t pos = path.find("./"); pos != String::npos && pos == 0) {
        p = path.substr(2);
    }
    
    return static_cast<String>(fs::absolute(p.c_str()));
}

String File::getFilename() const {
    String p = path;
    if(const size_t pos = p.find_last_of("/\\"); pos != String::npos) {
        return p.substr(pos + 1);
    }
    return p;
}

ByteArray File::getBytes() const {
    const std::filesystem::path inputFilePath{path.c_str()};
    const auto length = file_size(inputFilePath);

    ByteArray bytes(length);
    std::ifstream inputFile(path, std::ios_base::binary);
    inputFile.read((char *)bytes.data(), static_cast<long>(length));
    inputFile.close();
    return bytes;
}

bool File::exists(const String &path) {
    return fs::exists(path.c_str());
}

bool File::isDirectory(const String &path) {
    return fs::is_directory(path.c_str());
}

bool File::isReadable(const String &path) {
    return access(path.c_str(), R_OK) == 0;
}

bool File::isWritable(const String &path) {
    return access(path.c_str(), W_OK) == 0;
}

// private
File::File() = default;