cmake_minimum_required(VERSION 3.10)

# set the project name
project(cinnamon-discovery VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -pedantic")

find_package(SQLite3 REQUIRED)
include_directories(${SQLITE3_INCLUDE_DIR})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
file(GLOB_RECURSE SOURCES *.cpp)
include_directories(./include)

# add the executable
add_executable(cinnamon-discovery ${SOURCES})
target_link_libraries(cinnamon-discovery ${LIBXML2_LIBRARIES} ${CURL_LIBRARIES} sqlite3)