#include <filesystem>
#include "Dir.h"

namespace fs = std::filesystem;

string Dir::currentDir() {
    return fs::current_path();
}