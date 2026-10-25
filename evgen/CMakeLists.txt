cmake_minimum_required(VERSION 3.10)

project(videoingest)

set(CMAKE_BUILD_TYPE Debug)

# 1. Ensure PkgConfig is available
find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED IMPORTED_TARGET
    gstreamer-1.0
    gstreamer-video-1.0
    gstreamer-app-1.0
)

add_executable(videoingest src/GstVideoIngest.cpp)

target_link_libraries(videoingest PkgConfig::GSTREAMER)

target_include_directories(videoingest PUBLIC include)