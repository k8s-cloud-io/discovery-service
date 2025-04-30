#include <iostream>
#include "Logger.h"

void Logger::log(const String &msg) {
    std::cout << msg << std::endl;
}