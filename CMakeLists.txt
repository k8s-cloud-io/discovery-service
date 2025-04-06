cmake_minimum_required(VERSION 3.20)
include(FindPkgConfig)

# set the project name
project(cinnamon-discovery VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RULE_MESSAGES OFF)

include_directories(/usr/include)
include_directories(./src/include)

pkg_check_modules(SQLITE3 REQUIRED sqlite3)
include_directories(${SQLITE3_INCLUDE_DIRS})

pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)
include_directories(${LIBXML2_INCLUDE_DIRS})

pkg_check_modules(CURL REQUIRED libcurl)
include_directories(${CURL_INCLUDE_DIRS})

pkg_check_modules(GDKPIXBUF REQUIRED gdk-pixbuf-2.0)
include_directories( ${GDKPIXBUF_INCLUDE_DIRS} )

pkg_check_modules(JSON_GLIB REQUIRED json-glib-1.0)
include_directories( ${JSON_GLIB_INCLUDE_DIRS} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
file(GLOB_RECURSE SOURCES ./src/*.cpp)

# add the executable
add_executable(cinnamon-discovery ${SOURCES})
target_link_libraries(
        cinnamon-discovery
        ${LIBXML2_LIBRARIES}
        ${CURL_LIBRARIES}
        ${GDKPIXBUF_LIBRARIES}
        ${SQLITE3_LIBRARIES}
        ${JSON_GLIB_LIBRARIES}
)