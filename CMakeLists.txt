cmake_minimum_required(VERSION 3.20)
include(FindPkgConfig)

# set the project name
project(discovery-service VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
else(
    set(CMAKE_VERBOSE_MAKEFILE ON)
)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
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

pkg_check_modules(GIO REQUIRED gio-2.0)
include_directories( ${GIO_INCLUDE_DIRS} )

pkg_check_modules(JSON_CPP REQUIRED jsoncpp)
include_directories( ${JSON_CPP_INCLUDE_DIRS} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
file(GLOB_RECURSE SOURCES ./src/*.cpp)

# add the executable
add_executable(discovery-service ${SOURCES})
target_link_libraries(
        discovery-service
        ${LIBXML2_LIBRARIES}
        ${CURL_LIBRARIES}
        ${GDKPIXBUF_LIBRARIES}
        ${GIO_LIBRARIES}
        ${SQLITE3_LIBRARIES}
        ${JSON_CPP_LIBRARIES}
)