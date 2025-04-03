#include <filesystem>
#include "Dir.h"

namespace fs = std::filesystem;

String Dir::currentDir() {
    return static_cast<String>(fs::current_path());
}