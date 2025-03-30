#include <filesystem>
#include "Dir.h"

namespace fs = std::filesystem;

String Dir::currentDir() {
    return (String)fs::current_path();
}